#pragma once

#include <string>
#include <map>
#include <functional>

struct HotDrink;

class DrinkWithVolumeFactory
{
    std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;

public: 
    DrinkWithVolumeFactory()
    {
        factories["tea"] = [] {
            auto tea = std::make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };
    }

    std::unique_ptr<HotDrink> makeDrink(const std::string& name)
    {
        return factories[name]();
    }

};