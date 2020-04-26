#include <iostream>
#include <string>
#include <vector>

struct BankAccount
{
    int balance = 0;
    int overdraftLimit = -500;

    void deposit(int amount)
    {
        balance += amount;
        std::cout << "deposited " << amount << ", balance now " << balance << std::endl;
    }

    void withdraw(int amount)
    {
        if (balance-amount >= overdraftLimit)
        {
            balance -= amount;
            std::cout << "withdrew " << amount << ", balance now " << balance << std::endl;
        }
    }
};

struct Command
{
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;

    Command(BankAccount& account, const Action action, const int amount)
        : account{account},
          action{action},
          amount{amount}
    {}

    void call() const
    {
        switch (action)
        {

        case deposit: 
            account.deposit(amount);
            break;

        case withdraw: 
            account.withdraw(amount);
            break;

        default: break;

        }
    }
};

int main()
{
    BankAccount ba;
    std::vector<Command> commands{
        Command{ba, Command::deposit, 100},
        Command{ba, Command::withdraw, 200}  
    };

    for (auto& cmd : commands)
        cmd.call();

    return 0;
}