#include "Singleton.hpp"
#include <gtest/gtest.h>

TEST(DatabaseTests, IsSingletonTest)
{
    auto& db = SingletonDatabase::get();
    auto& db2 = SingletonDatabase::get();
    ASSERT_EQ(1, db, instanceCount);
    ASSERT_EQ(1, db, instanceCount);
}


int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return 0;
}