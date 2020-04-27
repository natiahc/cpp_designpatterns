
#include <iostream>
#include <string>
#include "ChatRoom.h"

int main()
{
	ChatRoom room;
	auto noel = room.join(Person{ "Noel" });
	auto joe = room.join(Person{ "Joe" });

	noel->say("hi room");
	joe->say("hey noel");

	auto ram = room.join(Person{ "Ram" });
	ram->say("hallo zusammen");

	noel->pm("Ram", "hello Ram, Wie geht es Ihnen?");

	return 0;
}