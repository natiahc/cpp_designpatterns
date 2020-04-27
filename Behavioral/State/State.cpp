#include <iostream>
#include <string>
#include <map>
#include <vector>

enum class State
{
	OffHook,
	Connecting,
	Connected,
	OnHold
};

inline std::ostream& operator<<(std::ostream& os, const State& s)
{
	switch (s)
	{
	case State::OffHook:
		os << "Off the hook";
		break;
	case State::Connecting:
		os << "Connecting";
		break;
	case State::Connected:
		os << "Connected";
		break;
	case State::OnHold:
		os << "OnHold";
		break;
	}

	return os;
}

enum class Trigger 
{
	CallDialed,
	HungUp,
	CallConnected,
	PlacedOnHold,
	TakenOffHold,
	LeftMessage
};

inline std::ostream& operator<<(std::ostream& os, const Trigger& t)
{
	switch (t)
	{
	case Trigger::CallDialed:
		os << "Call Dialed";
		break;
	case Trigger::HungUp:
		os << "Hung Up";
		break;
	case Trigger::CallConnected:
		os << "Call Connected";
		break;
	case Trigger::PlacedOnHold:
		os << "Placed On Hold";
		break;
	case Trigger::TakenOffHold:
		os << "Taken Off Hold";
		break;
	case Trigger::LeftMessage:
		os << "Left Message";
		break;
	}

	return os;
}

int main()
{
	std::map<State, std::vector<std::pair<Trigger, State>>> rules;
	rules[State::OffHook] = {
		{Trigger::CallDialed, State::Connecting}
	};

	rules[State::Connecting] = {
		{Trigger::HungUp, State::OffHook},
		{Trigger::CallConnected, State::Connected}
	};

	rules[State::Connected] = {
		{Trigger::LeftMessage, State::OffHook},
		{Trigger::HungUp, State::OffHook},
		{Trigger::PlacedOnHold, State::OffHook}
	};

	rules[State::OnHold] = {
		{Trigger::TakenOffHold, State::Connected},
		{Trigger::HungUp, State::OffHook}
	};

	State currentState{ State::OffHook };

	while (true)
	{
		std::cout << "The phone is currently " << currentState << std::endl;
	
	selectTrigger:
		std::cout << "Select a trigger: " << std::endl;
		
		int i = 0;
		for (auto item : rules[currentState])
		{
			std::cout << i++ << ". " << item.first << std::endl;
		}

		int input;
		std::cin >> input;
		if (input < 0 || (input + 1) < rules[currentState].size())
		{
			std::cout << "Incorrect option, please try again.\n";
			goto selectTrigger;
		}

		currentState = rules[currentState][input].second;
	}

	std::cout << "we are done using the phone" << std::endl;

	return 0;
}