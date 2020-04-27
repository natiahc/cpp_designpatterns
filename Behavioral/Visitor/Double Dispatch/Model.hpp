#pragma once

#include <string>
#include <vector>
#include <sstream>

struct Visitor;

struct Element
{
	virtual ~Element() = default;
	virtual void accept(Visitor& v) const = 0;
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

	void accept(Visitor& v) const override
	{
		v.visit(*this);
	}
};

struct ListItem : TextElement
{
	explicit ListItem(const std::string& text)
		: TextElement{ text }
	{}

	void accept(Visitor& v) const override
	{
		v.visit(*this);
	}
};

struct List : std::vector<ListItem>, Element	
{
	List(const std::initializer_list<value_type>& _IList)
		: std::vector<ListItem>(_IList)
	{}

	void accept(Visitor& v) const override
	{
		v.visit(*this);
	}
};