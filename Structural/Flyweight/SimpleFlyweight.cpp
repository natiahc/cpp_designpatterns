#include <sstream>
#include <iostream>
#include <boost\bimap.hpp>

typedef uint32_t key;

struct User
{
	User(const std::string& first_name, const std::string& last_name)
		: first_name{ add(first_name) },
		last_name{ add(last_name) }
	{}

	const std::string& get_first_name() const
	{
		return names.left.find(first_name)->second;
	}

	const std::string& get_last_name() const
	{
		return names.left.find(last_name)->second;
	}

	friend std::ostream& operator<<(std::ostream& os, const User& obj)
	{
		return os
			<< "first name: " << obj.first_name << " " << obj.get_first_name() 
			<< " last name: " << obj.last_name << " " << obj.get_last_name();
	}

protected:
	static boost::bimap<key, std::string> names;
	static int seed;

	static key add(const std::string& s)
	{
		auto it = names.right.find(s);
		if (it == names.right.end())
		{
			key id = ++seed;
			names.insert(boost::bimap<key, std::string>::value_type(seed, s));
			return id;
		}
		return it->second;
	}
	key first_name, last_name;
};

int User::seed = 0;
boost::bimap<key, std::string> User::names;

int main(int ac, char* av[])
{
	User sam_tavares{ "sam", "Tavares" };
	User john_tavares{ "John", "Tavares" };

	std::cout << "Sam: " << sam_tavares << std::endl;
	std::cout << "John: " << john_tavares << std::endl;

	return 0;
}