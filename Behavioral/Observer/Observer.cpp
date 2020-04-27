#include <iostream>
#include <string>
#include <mutex>
#include <vector>

#include <boost/any.hpp>

struct Person;
struct PersonListener
{
	virtual ~PersonListener() = default;
	virtual void personChanged(Person& p, const std::string& propertyName,
				const boost::any newValue) = 0;
};

static std::mutex mtx;

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
		std::lock_guard<std::mutex> guard{ mtx };
		if(std::find(std::begin(listeners), std::end(listeners), pl) == std::end(listeners))
			listeners.push_back(pl);
	}

	void unsubscribe(PersonListener* pl)
	{
		std::lock_guard<std::mutex> guard{ mtx };
		for (auto it=listeners.begin(); it!=listeners.end(); it++)
		{
			if (*it = pl)
				*it = nullptr;

		}
	}

	void notify(const std::string& propertyName, const boost::any newValue)
	{
		std::lock_guard<std::mutex> guard{ mtx };
		for (const auto listener : listeners)
		{
			if(listener)
				listener->personChanged(*this, propertyName, newValue);
		}

		listeners.erase(std::remove(listeners.begin(), listeners.end(), nullptr),
			listeners.end());
	}

private:
	int age;
	std::vector<PersonListener*> listeners;
};

struct BadListener : PersonListener
{
	void personChanged(Person& p, const std::string& propertyName,
		const boost::any newValue) override
	{
		p.unsubscribe(this);
	}
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
	//BadListener c1; // Reentrancy
	p.subscribe(&cl);
	p.subscribe(&cl);
	p.setAge(15);
	p.setAge(16);
	p.unsubscribe(&cl);
	p.setAge(17);

	return 0;
}