#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <memory>

#include <boost/lexical_cast.hpp>

struct Token
{
	enum Type { integer, plus, minus, lparen, rparen } type;
	std::string text;

	Token(const Type type, const std::string& text)
		: type{type},
		  text{text}
	{}

	friend std::ostream& operator<<(std::ostream& os, const Token& obj)
	{
		return os << "`" << obj.text << "`";
	}
};

struct Element
{
	virtual ~Element() = default;
	virtual int eval() const = 0;
};

struct Integer : Element
{
	int value;

	Integer(const int value)
		: value{value}
	{}

	int eval() const override
	{
		return value;
	}
};

struct BinaryOperation : Element
{
	enum Type { addition, subtraction } type;
	std::shared_ptr<Element> lhs;
	std::shared_ptr<Element> rhs;

	int eval() const override
	{
		if (type == addition)
		{
			return lhs->eval() + rhs->eval();
		}
		
		return lhs->eval() - rhs->eval();
	}
};

std::vector<Token> lex(const std::string& input)
{
	std::vector<Token> result;

	for (int i = 0; i < input.length(); ++i)
	{
		switch (input[i])
		{

		case '+': 
			result.push_back(Token{ Token::plus, "+" });
			break;
		case '-':
			result.push_back(Token{ Token::minus, "-" });
			break;
		case '(':
			result.push_back(Token{ Token::lparen, "(" });
			break;
		case ')':
			result.push_back(Token{ Token::rparen, ")" });
			break;
		default:
			std::ostringstream buffer;
			buffer << input[i];
			for (int j = i + 1; j < input.size(); ++j)
			{
				if (isdigit(input[j]))
				{
					buffer << input[j];
					++i;
				} 
				else
				{
					result.push_back(Token{ Token::integer, buffer.str() });
					break;
				}
			}
		}
	}

	return result;
}

std::shared_ptr<Element> parse(const std::vector<Token>& tokens)
{
	auto result = std::make_shared<BinaryOperation>();
	bool haveLhs = false;

	for (size_t i = 0; i < tokens.size(); i++)
	{
		auto token = tokens[i];

		switch (token.type)
		{
		case Token::integer: 
		{
			int value = boost::lexical_cast<int>(token.text);
			auto integer = std::make_shared<Integer>(value);
			if (!haveLhs)
			{
				result->lhs = integer;
				haveLhs = true;
			}
			else
				result->rhs = integer;
		}
		break;

		case Token::plus:
			result->type = BinaryOperation::addition;
			break;
		case Token::minus:
			result->type = BinaryOperation::subtraction;
			break;
		case Token::lparen:
		{
			int j = i;
			for (; j < tokens.size(); ++j)
			{
				if (tokens[j].type == Token::rparen)
					break;
			}

			std::vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
			auto element = parse(subexpression);
			if (!haveLhs)
			{
				result->lhs = element;
				haveLhs = true;
			}
			else
				result->rhs = element;

			i = j;
		}
		break;

		}
	}

	return result;
}

int main()
{
	std::string input{ "(13-4)-(12+1)" };
	auto tokens = lex(input);

	for (auto t : tokens)
	{
		std::cout << t << "   ";
	}

	std::cout << std::endl;

	auto parsed = parse(tokens);
	std::cout << input << " = " << parsed->eval() << std::endl;

	return 0;
}