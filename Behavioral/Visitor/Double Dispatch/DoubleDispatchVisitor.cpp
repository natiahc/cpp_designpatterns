#include <iostream>
#include <string>
#include <algorithm>

#include "Visitor.hpp"
#include "Model.hpp"

struct HtmlVisitor : Visitor
{
	void visit(const Paragraph& p) override
	{
		oss << "<p>" << p.text << "</p>\n";
	}

	void visit(const ListItem& li) override
	{
		oss << "<li>" << li.text << "</li>\n";
	}

	void visit(const List& l) override
	{
		oss << "<ul>\n";
		for (auto x : l)
		{
			x.accept(*this);
		}
		oss << "</ul>\n";
	}

	std::string str() override
	{
		return oss.str();
	}

private:
	std::ostringstream oss;
};

int main()
{
	Paragraph p{ "Here are some colors" };
	ListItem red{ "Red" };
	ListItem green{ "Green" };
	ListItem blue{ "Blue" };
	List color{ red, green, blue };

	std::vector<Element*> document{ &p, &color };
	HtmlVisitor v;
	for (auto x : document)
	{
		x->accept(v);
	}

	std::cout << v.str() << std::endl;

	return 0;
}