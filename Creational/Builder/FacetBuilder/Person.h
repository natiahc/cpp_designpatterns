#pragma once

#include <string>

class PersonBuilder;

class Person
{
    // address
    std::string streetAddress{};
    std::string postCode{};
    std::string city{};

    // employment
    std::string companyName{};
    std::string position{};
    int annualIncome{};

    Person(){}

public:
	static PersonBuilder create();

    Person(Person&& other)
        : streetAddress(std::move(other.streetAddress)),
          postCode(std::move(other.postCode)),
          city(std::move(other.city)),
          companyName(std::move(other.companyName)),
          position(std::move(other.position)),
          annualIncome(std::move(other.annualIncome))
    {}

    Person& operator=(Person&& other)
    {
        if (this == &other)
            return *this;

        streetAddress = std::move(other.streetAddress),
        postCode = std::move(other.postCode);
        city= std::move(other.city);
        companyName = std::move(other.companyName);
        position = std::move(other.position);
        annualIncome = std::move(other.annualIncome);

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& obj)
    {
        return os
            << "streetAddress: " << obj.streetAddress
            << " postCode: " << obj.postCode
            << " city: " << obj.city
            << " position: " << obj.postCode
            << " annualIncome: " << obj.annualIncome;
    }

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;

};