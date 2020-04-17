// Single Responsibility Principle : A class should only have a single responsibility

#include <string>
#include <vector>

struct Journal
{
    std::string title;
    std::vector<std::string> entries;

    explicit Journal(const std::string& title)
        : title{title}
    {}

    void add(const std::string& entry)
    {
        entries.push_back(entry);
    }
};

struct PersistenceManager
{
    static void save(const Journal& j, const std::string& filename)
    {
        std::ofstream ofs(filename);
        for (auto& s : j.entries)
            ofs << s << std::endl;
    }
};