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

template<typename LS>
struct TextProcessor
{
	TextProcessor() : list_strategy(std::make_unique<LS>())
	{}

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

private:
	std::ostringstream oss;
	std::unique_ptr<LS> list_strategy;
};

int main()
{
	TextProcessor<MarkdownListStrategy> tpm;
	tpm.append_list({ "foo", "bar", "baz" });
	std::cout << tpm.str() << std::endl;

	TextProcessor<HTMLListStrategy> tph;
	tph.append_list({ "foo", "bar", "baz" });
	std::cout << tph.str() << std::endl;

	return 0;
}