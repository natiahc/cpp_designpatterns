#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>

struct Shape
{
    virtual std::string str() const = 0;
};

struct Circle : Shape
{
    float radius;

    explicit Circle(const float radius)
        : radius{radius}
    {}

    void resize(float factor)
    {
        radius *= factor;
    }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape
{
    float side;

    Square(){}

    explicit Square(const float side)
        : side(side)
    {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A square with side = " << side;
        return oss.str();
    }
};

template<typename T> 
struct ColoredShape2 : T
{
    // to avoid misusing of with different interface class like for example
    // struct NotAShape { virtual std::string() const { return std::strng(); } };
    // ColoredShape2<NotAShape> legal; // which is completely legal
    // to avoid this we can use static assert
    static_assert(std::is_base_of<Shape,T>::value,
        "Template argument must be a Shape");

    std::string color;

    explicit ColoredShape2(const std::string& color)
        : color{color}
    {}

    std::string str() const override 
    {
        std::ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

template<typename T> 
struct TransparentShape2 : T
{
    uint8_t transparency;

    template<typename...Args>
    explicit TransparentShape2(const uint8_t transparency, Args ...args)
        : T::T(args...),
          transparency{transparency}
    {}

    std::string str() const override 
    {
        std::ostringstream oss;
        oss << T::str() << " has " 
        << static_cast<float>(transparency) / 255.f * 100.f
        << "% transparency";

        return oss.str();
    }
};

int main()
{
    TransparentShape2<Square> hidden_square{0, 15};
    std::cout << hidden_square.str() << std::endl;
    return 0;
}