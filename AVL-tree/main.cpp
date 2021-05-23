#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include "AVL-tree.hpp"

int main()
{
    auto comparator = [](std::string lword, std::string rword)
    {
        return lword.length() < rword.length();
    };
    AVL_tree< std::string, int, std::function< bool(std::string, std::string) > > dict(comparator);
    std::vector< std::pair< std::string, int > > vals
    {
        {"biba", 5},
        {"aye", 3},
        {"hui", 15},
        {"soldatkina", 1},
        {"miish", 49},
        {"weewee", 20},
        {"evgeny", 33},
        {"ayestalin", 11},
        {"kaliivan", 93},
        {"aboba", 24}
    };

    for (auto& pair: vals)
    {
        dict.insertPair(pair);
    }
    print(dict.getRoot(), std::cout, 7);
}