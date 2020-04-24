#include <iostream>
#include <string>
#include <sstream>

struct Shape
{
    virtual std::string str() const = 0;
};

struct Circle : Shape
{
    float radius;

    Circle(){}

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
    std::string color;

    ColoredShape2(){}

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

    TransparentShape2(){}

    explicit TransparentShape2(const uint8_t transparency)
        : transparency{transparency}
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
    ColoredShape2<Circle> red_circle{"red"};
    red_circle.radius = 5;
    std::cout << red_circle.str() << std::endl;

    TransparentShape2<ColoredShape2<Circle>> red_half_transparent_circle{127};
    red_half_transparent_circle.color = "red";
    red_half_transparent_circle.radius = 100;
    std::cout << red_half_transparent_circle.str() << std::endl;

    return 0;
}