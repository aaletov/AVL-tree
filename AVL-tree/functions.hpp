#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <deque>
#include <string>

bool dictComparator(std::string lword, std::string rword);
template < class Key, class T >
bool containsValues(std::deque<T*>& deque);
void formatWord(std::string& word);
bool filterWord(const std::string& word);
bool intComparator(int key1, int key2) { return key1 < key2; }

template <typename T>
bool containsValues(std::deque<T*>& deque)
{
    bool x = false;
    for (int i = 0; i < deque.size(); i++)
    {
        x = x || deque[i] != nullptr;
        if (x)
        {
            break;
        }
    }
    return x;
}

#endif