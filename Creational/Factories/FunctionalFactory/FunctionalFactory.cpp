#include <iostream>
#include <memory>
#include <map>

#include "HotDrink.h"
#include "DrinkWithVolumeFactory.h"

int main()
{
    DrinkWithVolumeFactory dvf;
    dvf.makeDrink("tea");
    return 0;
}