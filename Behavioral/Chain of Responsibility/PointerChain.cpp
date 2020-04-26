#include <iostream>
#include <string>

struct Creature
{
    std::string name;
    int attack;
    int defense;

    Creature(const std::string& name, const int attack, const int defense)
        : name{name},
          attack{attack},
          defense{defense}
    {}

    friend std::ostream& operator<< (std::ostream& os, const Creature& obj)
    {
        return os 
            << "name: " << obj.name
            << " attack: " << obj.attack
            << " defense: " << obj.defense;
    }
};

class CreatureModifier
{
    CreatureModifier* next = nullptr;

protected:
    Creature& creature;

public:
    explicit CreatureModifier(Creature& creature)
        : creature{creature}
    {}

    virtual ~CreatureModifier() = default;

    void add(CreatureModifier* cm)
    {
        if(next) next->add(cm);
        else next = cm;
    }

    virtual void handle()
    {
        if(next) next->handle();
    }
};

// 1. Double the creature's atttack
// 2. Increase defense by 1 unless power > 2
// 3. No bonuses can be applied to this creature

class NoBonusModifier : public CreatureModifier
{

public:
    explicit NoBonusModifier(Creature& creature)
        : CreatureModifier{creature}
    {}

    void handle() override
    {}
};

class DoubleAttackMofifier : public CreatureModifier
{

public:
    explicit DoubleAttackMofifier(Creature& creature)
        : CreatureModifier(creature)
    {}

    void handle() override
    {
        creature.attack *= 2;
        CreatureModifier::handle();
    }
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:
    explicit IncreaseDefenseModifier(Creature& creature)
        : CreatureModifier(creature)
    {}

    void handle() override
    {
        if (creature.attack <= 2)
            creature.defense++;

        CreatureModifier::handle();
    }
};

int main()
{
    Creature goblin{"Goblin", 1, 1};

    CreatureModifier root{goblin};
    DoubleAttackMofifier r1{goblin};
    DoubleAttackMofifier r1_2{goblin};
    IncreaseDefenseModifier r2{goblin};
    NoBonusModifier no{goblin};
    
    root.add(&no);
    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);

    root.handle();

    std::cout << goblin << std::endl;
    return 0;
}