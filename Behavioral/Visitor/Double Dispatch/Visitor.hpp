#pragma once

#include <string>

struct Paragraph;
struct ListItem;
struct List;
struct Visitor
{
	virtual ~Visitor() = default;

	virtual void visit(const Paragraph& p) = 0;
	virtual void visit(const ListItem& li) = 0;
	virtual void visit(const List& l) = 0;
	virtual std::string str() = 0;
};