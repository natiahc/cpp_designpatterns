#pragma once

#include <string>

class PersonAddressBuilder : public PersonBuilder
{
    typedef PersonAddressBuilder Self;

public:
    explicit PersonAddressBuilder(Person& person)
        : PersonBuilder{person}
    {}

    Self& at(std::string streetAddress)
    {
        person.streetAddress = streetAddress;
        return *this;
    }

    Self& withPostCode(std::string postCode)
    {
        person.postCode = postCode;
        return *this;
    }

    Self& in(std::string city)
    {
        person.city = city;
        return *this;
    }

};