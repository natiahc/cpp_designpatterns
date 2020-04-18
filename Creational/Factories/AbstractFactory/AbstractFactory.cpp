#include <iostream>
#include <memory>
#include <map>

#include "HotDrink.h"
#include "DrinkFactory.h"

// std::unique_ptr<HotDrink> makeDrink(std::string type)
// {
//     std::unique_ptr<HotDrink> drink;
//     if(type == "tea")
//     {
//         drink = std::make_unique<Tea>();
//         drink->prepare(200);
//     } 
//     else 
//     {
//         drink = std::make_unique<Coffee>();
//         drink->prepare(50);
//     }

//     return drink;
// }

int main()
{
    //auto d = makeDrink("tea");

    DrinkFactory df;
    df.makeDrink("coffee");

    return 0;
}