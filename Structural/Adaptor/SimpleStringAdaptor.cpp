#include <vector>
#include <stack>
#include <boost/algorithm/algorithm.hpp>
#include <iostream>

class String
{
    std::string s;

public:
    explicit String(const std::string& cs)
        : s{cs}
    {
    }

    String toLower() const
    {
        std::string ss{s};
        boost::to_lower(ss);
        return { ss }; // String{ss}
    }

    std::vector<std::string> split(const std::string& delimeter = " ") const
    {
        std::vector<std::string> result;
        boost::split(result, s, boost::is_any_of(delimeter),
            boost::token_compress_on);

        return result;
    }
};

int main()
{
    String s{ "Hello World" };

    auto parts = s.toLower().split();
    for (const auto& p : parts)
        std::cout << "<" << p << ">" << std::endl;

    return 0;
}