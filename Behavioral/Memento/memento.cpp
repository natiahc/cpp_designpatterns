#include <iostream>
#include <string>
#include <vector>

class Memento
{
	int balance;

public:
	Memento(const int balance)
		: balance(balance)
	{}

	friend class BankAccount;
	friend class BankAccount2;
};

class BankAccount
{
	int balance{ 0 };

public:
	explicit BankAccount(const int balance)
		: balance{ balance }
	{}

	void restore(const Memento& m)
	{
		balance = m.balance;
	}

	Memento deposit(int amount)
	{
		balance += amount;
		return { balance };
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount& ba)
	{
		return os << 
			"balance: " << ba.balance;
	}
};


class BankAccount2
{
	int balance{ 0 };
	std::vector<std::shared_ptr<Memento>> changes;
	int current;

public:
	explicit BankAccount2(const int balance)
		: balance{ balance }
	{
		changes.emplace_back(std::make_shared<Memento>(balance));
		current = 0;
	}

	void restore(const std::shared_ptr<Memento>& m)
	{
		if (m)
		{
			balance = m->balance;
			changes.push_back(m);
			current = changes.size() - 1;
		}
	}

	std::shared_ptr<Memento> deposit(int amount)
	{
		balance += amount;
		auto m = std::make_shared<Memento>(balance);
		changes.push_back(m);
		++current;
		return m;
	}

	std::shared_ptr<Memento> undo()
	{
		if (current > 0)
		{
			--current;
			auto m = changes[current];
			balance = m->balance;
		}

		return {};
	}

	std::shared_ptr<Memento> redo()
	{
		if (current + 1 < changes.size())
		{
			++current;
			auto m = changes[current];
			balance = m->balance;
			return m;
		}

		return {};
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount2& ba)
	{
		return os <<
			"balance: " << ba.balance;
	}
};

int main()
{
	//BankAccount ba{ 100 };
	//auto m1 = ba.deposit(50);
	//auto m2 = ba.deposit(25);
	//std::cout << ba << std::endl;

	//// undo to ml
	//ba.restore(m1);
	//std::cout << ba << std::endl;

	//// undo to m2
	//ba.restore(m2);
	//std::cout << ba << std::endl;

	BankAccount2 ba{100};
	ba.deposit(50);
	ba.deposit(25);
	std::cout << ba << std::endl;

	ba.undo();
	std::cout << "undo 1: " << ba << std::endl;

	ba.undo();
	std::cout << "undo 2: " << ba << std::endl;

	ba.redo();
	std::cout << "redo 1: " << ba << std::endl;


	return 0;
}