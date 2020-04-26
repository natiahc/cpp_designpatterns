#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

struct ICommand
{
    virtual ~ICommand() = default;
    virtual void call() const = 0;
    virtual void undo() const = 0;
};

struct Command : ICommand
{
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;

    Command(BankAccount& account, const Action action, const int amount)
        : account{account},
          action{action},
          amount{amount}
    {}

    void call() const override
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

    void undo() const override
    {
        switch (action)
        {

        case withdraw: 
            account.deposit(amount);
            break;

        case deposit: 
            account.withdraw(amount);
            break;

        default: break;

        }
    }
};

struct CommandList : std::vector<Command>, ICommand
{
    CommandList(const std::initializer_list<value_type>& _Ilist)
        : std::vector<Command>(_Ilist)
    {
    }

    void call() const override
    {
        for (auto& cmd : *this)
            cmd.call();
    }

    void undo() const override
    {
        std::for_each(rbegin(), rend(),
            [](const Command& cmd)
            {
                cmd.undo();
            });
    }
};

int main()
{
    BankAccount ba;
    CommandList commands{
        Command{ba, Command::deposit, 100},
        Command{ba, Command::withdraw, 200}  
    };

    std::cout << ba.balance << std::endl;

    commands.call();

    std::cout << ba.balance << std::endl;

    //undo
    commands.undo();
    std::cout << ba.balance << std::endl;

    return 0;
}