#include <iostream>
#include <string>
#include <algorithm>
#include <typeindex>
#include <map>

struct GameObject;
void collide(GameObject& first, GameObject& second);

struct GameObject
{
	virtual ~GameObject() = default;
	virtual std::type_index type() const = 0;
	virtual void collide(GameObject& other) { ::collide(*this, other); }
};

template<typename T> 
struct GameObjectImpl : GameObject
{
	std::type_index type() const override
	{
		return typeid(T);
	}
};

struct Planet : GameObjectImpl<Planet>{};
struct Asteroid : GameObjectImpl<Asteroid>{};
struct SpaceShip : GameObjectImpl<SpaceShip>{};

struct ArmedSpaceShip : SpaceShip 
{
	std::type_index type() const override
	{
		return typeid(ArmedSpaceShip);
	}
};

void spaceship_planet() { std::cout << "spaceship lands on planet\n"; }
void asteroid_planet() { std::cout << "Asteroid burns up in atmosphere\n"; }
void asteroid_spaceship() { std::cout << "Asteroid hits and destroys spaceship\n"; }
void asteroid_armed_spaceship() { std::cout << "spaceship shots Asteroid\n"; }

std::map<std::pair<std::type_index, std::type_index>, void(*)(void)> outcomes{
	{{typeid(SpaceShip), typeid(Planet)}, spaceship_planet},
	{{typeid(Asteroid), typeid(Planet)}, asteroid_planet},
	{{typeid(Asteroid), typeid(SpaceShip)}, asteroid_spaceship},
	{ {typeid(Asteroid), typeid(ArmedSpaceShip)}, asteroid_armed_spaceship}
};

void collide(GameObject& first, GameObject& second)
{
	auto it = outcomes.find({ first.type(), second.type() });
	if (it == outcomes.end())
	{
		it = outcomes.find({ second.type(), first.type() });
		if (it == outcomes.end())
		{
			std::cout << "objects pass each other harmlessly\n";
		}
	}

	it->second();
}

int main()
{
	Planet planet;
	ArmedSpaceShip spaceship;
	Asteroid asteroid;
	
	collide(planet, spaceship);
	collide(planet, asteroid);
	collide(spaceship, asteroid);
	planet.collide(planet); //collide(planet, planet);


	return 0;
}