// Dependency Inversion Principle: 
//1.  High-level modules should not depend on low-level modules. Both should depend ofn abstractions
//    Example: reporting component should depend on a ConsoleLogger, but can depend on an ILogger
//2.  Abstactions should not depend upon details. Details should depend upon abstractions.
//    In other words, dependencies on interfaces and supertypes is better than dependencies on concrete types.
//- Inverion of Control (IoC) - the actual process of creating abstractions and getting them to replace dependencies
//- Dependecy Injection - use of software frameworks to ensure that a component's dependencies are satisfied

#include "di.hpp"
#include <ostream>
#include <memory>
#include <iostream>

struct ILogger
{
    virtual ~ILogger()
    {}

    virtual void log(const std::string& s) = 0;
};

struct ConsoleLogger : ILogger
{
    void log(const std::string& s) override
    {
        std::cout << "LOG: " << s.c_str() << std::endl;
    }
};

struct Engine
{
    float volume = 5;
    int horse_power = 400;

    friend std::ostream& operator<<(std::ostream& os, const Engine& obj)
    {
        return os
            << "volume: " << obj.volume
            << " horse_power: " << obj.horse_power;
    }
};

struct Car
{
    std::shared_ptr<Engine> engine;
    std::shared_ptr<ILogger> logger;

    explicit Car(const std::shared_ptr<Engine>& engine, const std::shared_ptr<ILogger> iLogger)
        : engine{engine}, logger(iLogger)
    {
        logger->log("Created a car");
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Car& obj)
    {
        return os
            << "cars with engine: " << *obj.engine;
    }
};

int main()
{
    //auto e = std::make_shared<Engine>();
    //auto c = std::make_shared<Car>(e);

    // using boost di
    auto injector = boost::di::make_injector(
        boost::di::bind<ILogger>().to<ConsoleLogger>()
    );
    
    auto c = injector.create<std::shared_ptr<Car>>();

    std::cout << *c << std::endl;

    return 0;
}