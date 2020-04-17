// Liskov Substtution Principle: Objects in a program should be replaced with 
// instances of their subtypes w/o altering the correctness of the program

#include <iostream>

class Rectangle
{
protected:
    int width, height;

public:
    Rectangle(const int width, const int height)
        : width{width}, height{height}
    {}

    virtual int getWidth() const
    {
        return width;
    }

    virtual void setWidth(const int width)
    {
        this->width = width;
    }

    virtual int getHeight() const
    {
        return height;
    }

    virtual void setHeight(const int height)
    {
        this->height = height;
    }

    int Area() const { return width*height; }
};

class Square : public Rectangle
{
public:
    Square(int size)
        : Rectangle{size, size}
    {}

    void setWidth(const int width) override
    {
        this->width = height = width;
    }

    void setHeight(const int height) override
    {
        this->height = width = height;
    }
};

// process() is fundamentally correct
// however when we are using sqaure we are voilatinng the Liskov Substitution rule
void process(Rectangle& r)
{
    int w = r.getWidth();
    r.setHeight(10);

    std::cout << "expect area = " << (w*10)
        << ", got " << r.Area() << std::endl;
}

// so the correct way to implement this 
// is by using the RectangleFactory as below
struct RectangleFactory
{
    static Rectangle createRectangle(int w, int h);
    static Rectangle createSquare(int size);
};

int main()
{
    Rectangle r{ 5, 5 };
    process(r);

    Square s{5};
    process(s);

    return 0;
}