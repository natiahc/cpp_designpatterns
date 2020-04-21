#pragma once

struct Person
{
    // Pimpl Idiom: only one implementaion i.e. inner classs/struct
    // keeping the interface of Person unchanged
    struct PersonImpl;

    PersonImpl *impl;

    Person();
    ~Person();

    void greet();
};