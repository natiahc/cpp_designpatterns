#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAdressBuilder.h"
#include "PersonJobBuilder.h"

int main()
{
    Person p = Person::create()
        .lives().at("20 St-Inez").withPostCode("403001").in("Goa")
        .works().at("127.0.0.1").asA("Developer").earning(0e0);

    std::cout << p << std::endl;
    
    return 0;
}