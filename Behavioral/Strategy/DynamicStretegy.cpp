#include <iostream>
#include <string>
#include <vector>
#include <sstream>

enum class OutputFormat
{
	Markdown,
	Html
};

struct ListStrategy
{
	virtual ~ListStrategy() = default;
	virtual void start(std::ostringstream& oss) = 0;
	virtual void end(std::ostringstream& oss) = 0;
	virtual void add_list_item(std::ostringstream& oss, const std::string& item) = 0;
};

struct HTMLListStrategy : ListStrategy
{
	void start(std::ostringstream& oss) override
	{
		oss << "<ul>" << std::endl;
	}

	void end(std::ostringstream& oss) override
	{
		oss << "</ul>" << std::endl;
	}

	void add_list_item(std::ostringstream& oss, const std::string& item) override
	{
		oss << "<li>" << item << "</li>" << std::endl;
	}
};

struct MarkdownListStrategy : ListStrategy
{
	void start(std::ostringstream& oss) override
	{}

	void end(std::ostringstream& oss) override
	{}

	void add_list_item(std::ostringstream& oss, const std::string& item) override
	{
		oss << " * " << item << std::endl;
	}
};

struct TextProcessor
{
	void clear()
	{
		oss.str("");
		oss.clear();
	}

	std::string str() const
	{
		return oss.str();
	}

	void append_list(const std::vector<std::string> items)
	{
		list_strategy->start(oss);
		for (auto& item : items)
			list_strategy->add_list_item(oss, item);
		list_strategy->end(oss);
	}

	void set_output_format(OutputFormat format)
	{
		switch (format)
		{
		case OutputFormat::Markdown: 
			list_strategy = std::make_unique<MarkdownListStrategy>();
			break;
		case OutputFormat::Html: 
			list_strategy = std::make_unique<HTMLListStrategy>();
			break;
		default: break;
		}
	}

private:
	std::ostringstream oss;
	std::unique_ptr<ListStrategy> list_strategy;
};

int main()
{
	TextProcessor tp;
	tp.set_output_format(OutputFormat::Markdown);
	tp.append_list({ "foo", "bar", "baz" });
	std::cout << tp.str() << std::endl;

	tp.clear();
	tp.set_output_format(OutputFormat::Html);
	tp.append_list({ "foo", "bar", "baz" });
	std::cout << tp.str() << std::endl;

	return 0;
}