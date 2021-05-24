#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <algorithm>
#include "AVL-tree.hpp"
#include "print-int.hpp"

int main()
{
    /*
    auto comparator = [](std::string lword, std::string rword)
    {
        return std::lexicographical_compare(lword.begin(), lword.end(), rword.begin(), rword.end());
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
    */
    auto comparator = std::less< int >();
    AVL_tree< int, int, std::function< bool(int, int) > > dict(comparator);
    std::vector< std::pair< int, int > > vals
    {
        {5, 5},
        {3, 3},
        {15, 15},
        {1, 1},
        {49, 49},
        {20, 20},
        {33, 33},
        {11, 11},
        {93, 93},
        {24, 24}
    };
    for (auto& pair: vals)
    {
        dict.insertPair(pair);
        std::cout << "Inserted " << std::get< 0 >(pair) << '\n';
        printInt(dict, std::cout, 10);
    }
}