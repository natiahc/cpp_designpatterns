#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <sstream>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

// template<typename T>
// struct ICLoneable
// {
//     virtual T clone() = 0;
// };

struct Address
{
    std::string street;
    std::string city;
    int suite;

    friend std::ostream& operator<<(std::ostream& os, const Address& obj)
    {
        return os
            << "street: " << obj.street
            << " city: " << obj.city
            << " suite: " << obj.suite;
    }

private:
	friend class boost::serialization::access;

	template<typename Ar> void serialize(Ar& ar, const unsigned int version)
	{
		ar& street;
		ar& city;
		ar& suite;
	}
};

struct Contact
{
    std::string name;
	Address address;

	friend std::ostream& operator<<(std::ostream& os, Contact& obj)
	{
		return os << "name: " << obj.name
			<< " address: " << obj.address;
	}

private:
	friend class boost::serialization::access;

	template<typename Ar> void serialize(Ar& ar, const unsigned int version)
	{
		ar& name;
		ar& address;
	}
};

int main()
{
	Contact noel;
	noel.name = "Noel tava";
	noel.address = Address{"St-Inez", "Panaji", 403001};

	auto clone = [](Contact c)
	{
		std::ostringstream oss;
		boost::archive::text_oarchive oa(oss);
		oa << c;

		std::string s = oss.str();

		Contact result;
		std::istringstream iss(s);
		boost::archive::text_iarchive ia(iss);
		ia >> result;
		return result;

	};

	Contact sam = clone(noel);
	sam.name = "Sam";
	sam.address.street = "caranzalem";

	std::cout << noel << std::endl << sam << std::endl;

    return 0;
}