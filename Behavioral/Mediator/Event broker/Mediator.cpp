#include <iostream>
#include <string>
#include <vector>
#include <boost/signals2.hpp>

struct Event
{
	virtual ~Event() = default;
	virtual void print() const = 0;
};

struct Player;

struct PlayerScored : Event
{
	std::string playerName;
	int goalsScoreSoFar;

	PlayerScored(const std::string& playerName, const int goalsScoreSoFar)
		: playerName{ playerName }, goalsScoreSoFar{ goalsScoreSoFar }
	{}

	void print() const override
	{
		std::cout << playerName << " has scored! (their " << goalsScoreSoFar << "goal)" << std::endl;
	}
};

struct Game	// event bus / broker
{
	boost::signals2::signal<void(Event*)> events; // observer
};

struct Player
{
	std::string name;
	int goalsScored = 0;
	Game& game;

	Player(const std::string& name, Game& game)
		: name{name},
		  game{game}
	{}

	void score()
	{
		goalsScored++;
		PlayerScored ps{ name, goalsScored };
		game.events(&ps);
	}
};

struct Coach
{
	Game& game;

	explicit Coach(Game& game)
		: game{ game }
	{
		game.events.connect([](Event* e)
		{
			PlayerScored* ps = dynamic_cast<PlayerScored*>(e);
			if (ps && ps->goalsScoreSoFar < 3)
			{
				std::cout << "Coach says well done, " << ps->playerName << std::endl;
			}
		});
	}
};

int main()
{
	Game game;
	Player player{"Carl", game};
	Coach coach{ game };

	player.score();
	player.score();
	player.score();

	return 0;
}