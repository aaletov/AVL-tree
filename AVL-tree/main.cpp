#include <iostream>
#include <vector>
#include <functional>
#include "node-operations.hpp"

int main()
{
    auto* dict = new node_t< std::string, int >;
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
    for (auto& pair : vals)
    {
        insertPair<  >(dict, pair);
    }
    print(dict, std::cout, 10);
}