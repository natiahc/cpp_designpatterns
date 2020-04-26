#include <iostream>
#include <string>

#include <boost/signals2.hpp>

struct Query
{
	std::string creatureName;
	enum Argument { attack, defense } argument;
	int result;

	Query(const std::string& creatureName, const Argument argument, const int result)
		: creatureName{ creatureName },
		argument{ argument },
		result{ result }
	{}
};

struct Game
{
	boost::signals2::signal<void(Query&)> query;
};

struct Creature
{
	Game &game;
	int attack;
	int defense;

public:
	std::string name;

	Creature(Game& game, const int attack, const int defense, const std::string& name)
		: game{ game },
		attack{ attack },
		defense{ defense },
		name{ name }
	{}

	int getAttack() const
	{
		Query q{ name, Query::Argument::attack, attack };
		game.query(q);
		return q.result;
	}

	friend std::ostream& operator<<(std::ostream& os, const Creature& obj)
	{
		return os
			<< "attack: " << obj.getAttack() // <-
			<< " defence: " << obj.defense
			<< " name: " << obj.name;
	}
};

class CreatureModifier
{
	Game& game;
	Creature& creature;

public:
	CreatureModifier(Game& game, Creature& Creature)
		: game{ game },
		creature{ creature }
	{}

	virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier : public CreatureModifier
{
	boost::signals2::connection conn;

public:
	DoubleAttackModifier(Game&  game, Creature& creature)
		: CreatureModifier(game, creature)
	{
		conn = game.query.connect([&](Query& q)
		{
			if (q.creatureName == creature.name &&
				q.argument == Query::Argument::attack)
			{
				q.result *= 2;
			}
		});
	}

	virtual ~DoubleAttackModifier()
	{
		conn.disconnect();
	}
};

int main(int ac, char* av[])
{
	Game game;
	Creature goblin{ game, 2, 2, "Strong Goblin" };

	std::cout << goblin << std::endl;

	{
		DoubleAttackModifier dam{ game, goblin };

		std::cout << goblin << std::endl;
	}

	std::cout << goblin << std::endl;

	return 0;
}