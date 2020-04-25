#include <iostream>
#include <ostream>
#include <memory>
#include <string>

struct Pingable
{
    virtual ~Pingable() = default;
    virtual std::wstring ping(const std::wstring& message) = 0;
};

struct Pong : Pingable
{
    std::wstring ping(const std::wstring& message) override
    {
        return message + L" pong";
    }
};

struct RemotePong : Pingable
{

};

void tryit(Pingable& p)
{
    std::wcout << p.ping(L"ping") << "\t";
}

int main()
{
    Pong pp;
    for (size_t i=0; i<10; i++)
    {
        tryit(pp);
    }

    return 0;
}