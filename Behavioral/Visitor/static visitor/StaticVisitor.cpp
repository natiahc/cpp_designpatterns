#include <iostream>
#include <string>
#include <algorithm>

#include "Model.hpp"

int main()
{
	Paragraph p{ "Here are some colors" };
	ListItem red{ "Red" };
	ListItem green{ "Green" };
	ListItem blue{ "Blue" };
	List color{ red, green, blue };

	std::vector<Element*> document{ &p, &color };
	std::ostringstream oss;
	std::for_each(std::begin(document), std::end(document),
		[&](const Element* e)
	{
		e->print(oss);
	});

	std::cout << oss.str() << std::endl;

	return 0;
}