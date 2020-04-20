#include "Singleton.hpp"
#include <gtest/gtest.h>

TEST(RecordFinderTests, SingletonTotalPoplulationTest)
{
    SingletonRecordFinder rf;
    std::vector<std::string> names{"London", "Berlin" };
    int tp = rf.totalPolulation(names);
    EXPECT_EQ(1614 + 1317, tp);
}

// Singleton is not a good approach 
// instead of explicity contraining data in lifetime
// better to use something like dependecy injection 
TEST(RecordFinderTests, DependentTotalPoplulationTest)
{
    DummDatabases db{};
    ConfigurabeRecordFinder rf{db};
    EXPECT_EQ(4, rf.totalPolulation(std::vector<std::string>{"alpha", "gamma"}));
}


int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return 0;
}