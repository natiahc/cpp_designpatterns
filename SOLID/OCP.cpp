// Open Close Principle: Entities should be open for extension but closed for modification

#include <iostream>
#include <string>
#include <vector>

enum class Color {Red, Green, Blue};
enum class Size {Small, Medium, Large};

struct Product
{
    std::string name;
    Color color;
    Size size;
};  

template<typename T> struct ISpecification
{
    virtual bool is_satisfied(T* item) = 0;
};

template<typename T> struct IFilter
{
    virtual std::vector<T*> filter(std::vector<T*> items, ISpecification<T>& spec) = 0;
};

struct BetterFilter : IFilter<Product>
{
    typedef std::vector<Product*> Items;
    std::vector<Product*> filter(std::vector<Product*> items, ISpecification<Product>& spec) override
    {
        Items result;
        for (auto& p : items)
            if (spec.is_satisfied(p))
                result.push_back(p);

        return result;
    }
};

struct ColorSpecification : ISpecification<Product>
{
    Color color;
    explicit ColorSpecification(const Color color)
        : color{color}
    {}

    bool is_satisfied(Product* item) override
    {
        return item->color == color;
    }
};

struct SizeSpecification : ISpecification<Product>
{
    Size size;
    explicit SizeSpecification(const Size size)
        : size{size}
    {}

    bool is_satisfied(Product* item) override
    {
        return item->size == size;
    }
};

template<typename T> struct AndSpecification : ISpecification<T>
{
    ISpecification<T>& first;
    ISpecification<T>& second;

    AndSpecification(ISpecification<T>& first, ISpecification<T>& second)
        : first{first}, second{second}
    {}

    bool is_satisfied(T* item) override
    {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

int main()
{
    Product orange{"orange", Color::Red, Size::Small};
    Product table{"table", Color::Red, Size::Large};
    Product car{"car", Color::Green, Size::Large};

    std::vector<Product*> all{&orange, &table, &car};

    BetterFilter bf;
    ColorSpecification red(Color::Red);

    auto redThings = bf.filter(all, red);
    for (auto& x : redThings)
        std::cout << x->name << " is red" << std::endl;

    SizeSpecification big(Size::Large);
    AndSpecification<Product> redAndBig(big, red);

    auto redBigThings = bf.filter(all, redAndBig);
    for (auto& x : redBigThings)
        std::cout << x->name << " is red and big" << std::endl;

    return 0;
}