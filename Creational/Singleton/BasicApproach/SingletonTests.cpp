#include "Singleton.hpp"
#include <gtest/gtest.h>

TEST(DatabaseTests, IsSingletonTest)
{
    auto& db = SingletonDatabase::get();
    auto& db2 = SingletonDatabase::get();
    ASSERT_EQ(1, db, instanceCount);
    ASSERT_EQ(1, db, instanceCount);
}

TEST(RecordFinderTests, SingletonTotalPoplulationTest)
{
    SingletonRecordFinder rf;
    std::vector<std::string> names{"London", "Berlin" };
    int tp = rf.totalPolulation(names);
    EXPECT_EQ(1614 + 1317, tp);
}


int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return 0;
}