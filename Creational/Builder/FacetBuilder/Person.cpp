#include "Person.h"
#include "PersonBuilder.h"

inline PersonBuilder Person::create()
{
    return PersonBuilder{};
}