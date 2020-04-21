#include <cstdio>
#include <memory>
#include <iostream>
#include <vector>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

// 2 + (3+4)
struct Expression
{
    virtual double eval() = 0;
    virtual void collect(std::vector<double>& v) = 0;
};

struct Literal : Expression
{
    double value;

    explicit Literal(const double value)
        : value{value}
    {}

    double eval() override
    {
        return value;
    }

    void collect(std::vector<double>& v) override
    {
        v.push_back(value);
    }
};

struct AdditionExpression : Expression
{
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

    AdditionExpression(const std::shared_ptr<Expression>& left,
                    const std::shared_ptr<Expression>& right)
                    : left{left},
                      right{right}
    {}

    double eval() override
    {
        return left->eval() + right->eval();
    }

    void collect(std::vector<double>& v) override
    {
        left->collect(v);
        right->collect(v);
    }
};

int main(int ac, char* av[])
{
    AdditionExpression sum{
        std::make_shared<Literal>(2),
        std::make_shared<AdditionExpression>(
            std::make_shared<Literal>(3),
            std::make_shared<Literal>(4)
        )
    };

    std::cout << "2+(3+4) = " << sum.eval() << std::endl;

    std::vector<double> v;
    sum.collect(v);

    for ( auto x : v )
        std::cout << x << "\t";

    std::cout << std::endl;

    // for finding average
	std::vector<double> values{ 0,1,2,3,4,5,6 };
	boost::accumulators::accumulator_set<double,
	boost::accumulators::stats<boost::accumulators::tag::mean>> acc;
	for (auto x : values)
		acc(x);

	std::cout << "average: " << boost::accumulators::mean(acc));



    return 0;
}