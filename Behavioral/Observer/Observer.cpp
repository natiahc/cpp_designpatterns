#include <iostream>
#include <string>
#include <vector>

#include <boost/any.hpp>

struct Person;
struct PersonListener
{
	virtual ~PersonListener() = default;
	virtual void personChanged(Person& p, const std::string& propertyName,
				const boost::any newValue) = 0;
};

struct Person 
{
	explicit Person(const int age)
		: age{ age }
	{}

	virtual int getAge() const
	{
		return age;
	}

	virtual void setAge(const int age)
	{
		if (this->age == age) return;

		auto OldCanVote = getCanVote();

		this->age = age;
		notify("age", this->age);

		auto newCanVote = getCanVote();
		if (OldCanVote != newCanVote)
		{
			notify("CanVote", newCanVote);
		}
	}

	bool getCanVote() const
	{
		return age >= 16;
	}

	void subscribe(PersonListener* pl)
	{
		listeners.push_back(pl);
	}

	void notify(const std::string& propertyName, const boost::any newValue)
	{
		for (const auto listener : listeners)
		{
			listener->personChanged(*this, propertyName, newValue);
		}
	}

private:
	int age;
	std::vector<PersonListener*> listeners;
};

struct ConsoleListener : PersonListener
{
	void personChanged(Person& p, const std::string& propertyName,
		const boost::any newValue) override
	{
		std::cout << "person's " << propertyName << " has been changed to ";
		if (propertyName == "age")
		{
			std::cout << boost::any_cast<int>(newValue);
		}
		else if (propertyName == "CanVote")
		{
			std::cout << boost::any_cast<bool>(newValue);
		}

		std::cout << std::endl;
	}
};

int main()
{
	Person p{ 14 };
	ConsoleListener cl;
	p.subscribe(&cl);
	p.setAge(15);
	p.setAge(16);

	return 0;
}