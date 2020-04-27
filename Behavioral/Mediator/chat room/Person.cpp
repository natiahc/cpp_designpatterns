#include "Person.h"
#include "ChatRoom.h"

#include <iostream>

Person::Person(const std::string & name)
	: name{name}
{
}

void Person::say(const std::string & message) const
{
	room->broadcast(name, message);
}

void Person::receive(const std::string & origin, const std::string & message)
{
	std::string s{ origin + ":\"" + message + "\"" };
	std::cout << "[" << name << "'s chat session] " << s << std::endl;
	chatLog.emplace_back(s);
}

void Person::pm(const std::string & who, const std::string & message)
{
	room->message(name, who, message);
}
