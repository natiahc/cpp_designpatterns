#include <iostream>
#include <string>

template<typename T> struct Maybe;

template<typename T>
Maybe<T> maybe(T* context)
{
    return  Maybe<T>(context);
}

template<typename T> 
struct Maybe
{
    T* context;

    explicit Maybe(T* const context)
        : context{context}
    {}

    template<typename Func>
    auto With(Func evaluator)
    {
        if(context == nullptr)
        {
            return Maybe<typename std::remove_pointer<decltype(evaluator(context))>::type>(nullptr);
        }
        else
        {
            return maybe(evaluator(context));
        }
    }

    template<typename Func>
    auto Do(Func action)
    {
        if(context != nullptr) 
            action(context);

        return *this;
    }
};

struct Address
{
    std::string* houseName = nullptr;
};

struct Person
{
    Address* address = nullptr;
};

void printhouseName(Person *p)
{
    // ugly way
    //if(p != nullptr && p->address != nullptr && p->address->houseName != nullptr)
    //    std::cout << *p->address->houseName << std::endl;
    
    maybe(p)
        .With([](auto x) { return x->address; })
        .With([](auto x) { return x->houseName; })
        .Do([](auto x) {std::cout << *x << std::endl; });
}

int main()
{
    Person p;
    p.address = new Address;
    p.address->houseName = new std::string("name");

    printhouseName(&p);

    delete p.address->houseName;
    delete p.address;

    return 0;
}