#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

class SingletonDatabase
{
    SingletonDatabase()
    {
        std::cout << "Initializing database" << std::endl;

        std::fstream ifs("capitals.txt");

        std::string s, s2;
        while(std::getline(ifs, s))
        {
            std::getline(ifs, s2);
            int pop = boost::lexical_cast<int>(s2);
            capitals[s] = pop;
        }

        instanceCount++;
    }

    std::map<std::string, int> capitals;

public:
    static int instanceCount;
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }

    int getPopulation(const std::string& name)
    {
        return capitals[name];
    }
};

int SingletonDatabase::instanceCount = 0;
struct SingletonRecordFinder
{
    int totalPolulation(std::vector<std::string> names)
    {
        int result = 0;
        for (auto& name : names)
        {
            result += SingletonDatabase::get().getPopulation(name);
        }

        return result;
    }
};