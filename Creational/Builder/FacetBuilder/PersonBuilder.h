#pragma once

#include "Person.h"

class PersonJobBuilder;
class PersonAddressBuilder;

class PersonBuilder
{
    Person p;

protected:
    Person& person;

    explicit PersonBuilder(Person& person)
        : person{person}
    {}

public:
    PersonBuilder() : person{p} {}

    operator Person()
    {
        return std::move(person);
    }

    PersonAddressBuilder lives();
    PersonJobBuilder works();

};