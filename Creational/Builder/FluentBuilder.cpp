#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

struct HtmlBuilder;

struct HtmlElement
{
    std::string name;
    std::string text;
    std::vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement(){}

    HtmlElement(const std::string& name, const std::string& text)
        : name{name}, text{text}
    {}

    std::string str(int indent = 0) const
    {
        std::ostringstream oss;
        std::string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << std::endl;

        if (text.size() > 0)
            oss << std::string(indent_size * (indent+1), ' ') << text << std::endl;

        for (const auto& e : elements)
            oss << e.str(indent+1);

        oss << i << "</" << name << ">" << std::endl;

        return oss.str();
    }

    static HtmlBuilder build(std::string rootName);
    static std::unique_ptr<HtmlBuilder> create(std::string rootName);
};

struct HtmlBuilder
{
    HtmlBuilder(std::string rootName)
    {
        root.name = rootName;
    }

    HtmlBuilder& addChild(std::string childName, std::string childText)
    {
        HtmlElement e{childName, childText};
        root.elements.emplace_back(e);
        return *this;
    }

    // HtmlBuilder* addChild2(std::string childName, std::string childText)
    // {
    //     HtmlElement e{childName, childText};
    //     root.elements.emplace_back(e);
    //     return this;
    // }

    std::string str() const 
    {
        return root.str();
    }

    operator HtmlElement()
    {
        return root;
    }

    HtmlElement root;
};

HtmlBuilder HtmlElement::build(std::string rootName)
{
    return HtmlBuilder{rootName};
}

// std::unique_ptr<HtmlBuilder> HtmlElement::create(std::string rootName)
// {
//     return std::make_unique<HtmlBuilder>(rootName);
// }

int main()
{
    HtmlBuilder builder{"ul"};
    builder.addChild("li", "Hello").addChild("li", "World");

    HtmlElement e = HtmlElement::build("ul").addChild("li", "Hello");

    //HtmlElement ee = HtmlElement::create("ul")->addChild2("li", "hello");

    std::cout << e.str();

    return 0;
}