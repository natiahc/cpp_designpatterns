#include <iostream>
#include <vector>

struct GraphicsObject
{
    virtual void draw() = 0;
};

struct Circle : GraphicsObject
{
    void draw() override
    {
        std::cout << "Circle" << std::endl;
    }
};

struct Group : GraphicsObject
{
    std::string name;
    std::vector<GraphicsObject*> objects;

    Group(const std::string& name) : name{name}
    {

    }

    void draw() override
    {
        std::cout << "Group " << name.c_str() << " contains: " << std::endl;
        for ( auto&& o : objects)
            o->draw();
    }
};

int main()
{
    Group root{"root"};
    Circle c1, c2;
    root.objects.push_back(&c1);

    Group subgroup("sub");
    subgroup.objects.push_back(&c2);

    root.objects.push_back(&subgroup);

    root.draw();

    return 0;
}