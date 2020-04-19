#include <iostream>
#include <sstream>

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

int main()
{
    Contact employee{"", new Address{"st-Inez, Panaji", "Panaji", 0}};

    Contact noel{employee};
    noel.name = "Noel";
    noel.workAddress->suite = 100;

    Contact ram{employee};
    ram.name = "Ram";
    ram.workAddress->suite = 146;

    std::cout << noel << std::endl << ram << std::endl;

    return 0;
}