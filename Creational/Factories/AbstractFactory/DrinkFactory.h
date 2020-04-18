#pragma once

#include <string>
#include <map>

#include "TeaFactory.h"
#include "CoffeeFactory.h"

struct HotDrink;

class DrinkFactory
{
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> factories;

public:
    DrinkFactory()
    {
        factories["coffee"] = std::make_unique<CoffeeFactory>();
        factories["tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> makeDrink(const std::string& name)
    {
        auto drink = factories[name]->make();
        drink->prepare(200); 
        return drink;
    }
};