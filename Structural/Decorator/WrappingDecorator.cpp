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

    explicit Circle(const float radius)
        : radius{radius}
    {}

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

struct ColoredShape : Shape
{
    Shape& shape;
    std::string color;

    explicit ColoredShape(Shape& shape, const std::string& color)
        : shape{shape},
          color{color}
    {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }   
};

struct TransparentShape : Shape
{
    Shape& shape;
    uint8_t transparency;

    explicit TransparentShape(Shape& shape, const uint8_t transparency)
        : shape{shape},
          transparency{transparency}
    {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has " 
        << static_cast<float>(transparency) / 255.f * 100.f
        << "% transparency";

        return oss.str();
    }   
};

int main()
{
    Circle circle{5};
    std::cout << circle.str() << std::endl;

    ColoredShape red_circle{circle, "red"};
    std::cout << red_circle.str() << std::endl;

    TransparentShape half_transparent_circle{circle, 128};
    std::cout << half_transparent_circle.str() << std::endl;

    TransparentShape half_transparent_red_circle{red_circle, 128};
    std::cout << half_transparent_red_circle.str() << std::endl;

    return 0;
}