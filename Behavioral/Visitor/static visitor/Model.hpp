#pragma once

#include <string>
#include <vector>
#include <sstream>

struct Element
{
	virtual ~Element() = default;
	virtual void print(std::ostringstream& oss) const = 0;
};

struct TextElement : Element
{
	std::string text;

	explicit TextElement(const std::string& text)
		: text{text}
	{}
};

struct Paragraph : TextElement
{
	explicit Paragraph(const std::string& text)
		: TextElement{ text }
	{}

	void print(std::ostringstream& oss) const override
	{
		oss << "<p>" << text << "</p>\n";
	}
};

struct ListItem : TextElement
{
	explicit ListItem(const std::string& text)
		: TextElement{ text }
	{}

	void print(std::ostringstream& oss) const override
	{
		oss << "<li>" << text << "</li>\n";
	}
};

struct List : std::vector<ListItem>, Element	
{
	List(const std::initializer_list<value_type>& _IList)
		: std::vector<ListItem>(_IList)
	{}

	void print(std::ostringstream& oss) const override
	{
		oss << "<ul>\n";
		for (auto li : *this)
			li.print(oss);
		oss << "</ul>\n";
	}
};