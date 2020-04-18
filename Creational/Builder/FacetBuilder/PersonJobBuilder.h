#pragma once

#include "PersonBuilder.h"

class PersonJobBuilder : public PersonBuilder
{
    typedef PersonJobBuilder Self;

public:
    explicit PersonJobBuilder(Person& person)
        : PersonBuilder{person}
    {}

    Self& at(std::string companyName)
    {
        person.companyName = companyName;
        return *this;
    }

    Self& asA(std::string position)
    {
        person.position = position;
        return *this;
    }

    Self& earning(int annualIncome)
    {
        person.annualIncome = annualIncome;
        return *this;
    }

};