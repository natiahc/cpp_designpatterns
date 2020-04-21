#include "Person.h"

#include <iostream>

struct Person::PersonImpl
{
    void greet();
};

void Person::PersonImpl::greet()
{
    std::cout << "hello";
}

Person::Person()
    : impl(new PersonImpl)
{}

Person::~Person()
{
    delete impl;
}

void Person::greet()
{
    impl->greet();
}