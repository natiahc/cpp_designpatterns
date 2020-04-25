#include <iostream>
#include <memory>
#include <string>

#include <boost\lexical_cast.hpp>

struct Logger
{
	virtual ~Logger() = default;
	virtual void info(const std::string& s) = 0;
	virtual int warn(const std::string& s) = 0;
};

struct BankAccount
{
	std::shared_ptr<Logger> log;
	std::string name;
	int balance = 0;

	BankAccount(const std::shared_ptr<Logger>& logger, const std::string& name,
		const int balance)
		: log{ logger },
		name{ name },
		balance{ balance }
	{}

	void deposit(int amount)
	{
		balance += amount;
		log->info("Desposited INR" + boost::lexical_cast<std::string>(amount)
			+ "to " + name + ", balance is now $" + boost::lexical_cast<std::string>(balance));
	}

	void withdraw(int amount)
	{
		if (balance >= amount)
		{
			balance -= amount;
			log->info("Withdraw INR" + boost::lexical_cast<std::string>(amount)
				+ " to " + name + ", balance is now $" + boost::lexical_cast<std::string>(balance));
		}
		else
		{
			log->warn("Tried to withdraw INR" + boost::lexical_cast<std::string>(amount)
				+ " from " + name + " but could not due to low balance");
		}

	}
};

struct ConsoleLogger : Logger
{
	int count = 0;

	void info(const std::string& s) override
	{
		std::cout << "INFO: " << s << std::endl;
	}

	int warn(const std::string& s) override
	{
		std::cout << "WARNING!! " << s << std::endl;
		return count++;
	}
};

struct NullLogger : Logger
{
	int warning_count;

	NullLogger() = default;

	explicit NullLogger(const int warning_count)
		: warning_count{warning_count}
	{}

	void info(const std::string& s) override
	{
	}

	int warn(const std::string& s) override
	{
		return warning_count;
	}
};

int main(int ac, char* av[])
{
	//auto logger = std::make_shared<ConsoleLogger>();
	//BankAccount account{ logger, "Primary account", 10000 };
	//account.deposit(1000);
	//account.withdraw(25000);
	//account.withdraw(1000);

	auto logger = std::make_shared<NullLogger>();
	BankAccount account{ logger, "Primary account", 10000 };
	account.deposit(1000);
	account.withdraw(25000);
	account.withdraw(1000);

	return 0;
}
