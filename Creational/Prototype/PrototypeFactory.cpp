#include <iostream>
#include <sstream>
#include <memory>

struct Address
{
    std::string street;
    std::string city;
    int suite;

    friend std::ostream& operator<<(std::ostream& os, const Address& obj)
    {
        return os
            << "street: " << obj.street
            << ", city: " << obj.city
            << ", suite: " << obj.suite;
    }
};

struct Contact
{
    std::string name;
    Address* workAddress;

    Contact(const std::string& name, Address* const workAddress)
        : name{name},
          workAddress{new Address{*workAddress}}
        {}

    Contact(const Contact& other)
        : name{other.name},
          workAddress{new Address{*other.workAddress}}
        {}

    ~Contact()
    {
        delete workAddress;
        workAddress = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Contact& obj)
    {
        return os
            << "name: " << obj.name
            << ", workAddress: " << *obj.workAddress;
    }
};

struct EmployeeFactory
{
    static Contact main;
    static Contact aux;

    static std::unique_ptr<Contact> newMainOfficeEmployee(std::string name, int suite)
    {
        return NewEmployee(name, suite, main);
    }

    static std::unique_ptr<Contact> newAuxOfficeEmployee(std::string name, int suite)
    {
        return NewEmployee(name, suite, aux);
    }

private:
    static std::unique_ptr<Contact> NewEmployee(std::string name, int suite,
        Contact& proto)
    {
        auto result = std::make_unique<Contact>(proto);
        result->name = name;
        result->workAddress->suite = suite;
        return result;
    }

};

Contact EmployeeFactory::main{"", new Address{"20 St-Inez", "Goa", 0}};
Contact EmployeeFactory::aux{"", new Address{"10 St-Inez", "Goa", 0}};

int main()
{
    auto noel = EmployeeFactory::newMainOfficeEmployee("Noel", 100);
    auto ram = EmployeeFactory::newAuxOfficeEmployee("Ram", 146);

    std::cout << *noel << std::endl << *ram << std::endl;

    return 0;
}