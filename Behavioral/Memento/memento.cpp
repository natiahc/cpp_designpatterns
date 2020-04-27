#include <iostream>
#include <string>

class Memento
{
	int balance;

public:
	Memento(const int balance)
		: balance(balance)
	{}

	friend class BankAccount;
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

int main()
{
	BankAccount ba{ 100 };
	auto m1 = ba.deposit(50);
	auto m2 = ba.deposit(25);
	std::cout << ba << std::endl;

	// undo to ml
	ba.restore(m1);
	std::cout << ba << std::endl;

	// undo to m2
	ba.restore(m2);
	std::cout << ba << std::endl;
	return 0;
}