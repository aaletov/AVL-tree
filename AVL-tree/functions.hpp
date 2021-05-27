#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <deque>
#include <string>

bool dictComparator(std::string lword, std::string rword);
template < class Key, class T >
bool containsValues(std::deque<T*>& deque);
void formatWord(std::string& word);
bool filterWord(const std::string& word);

template <typename T>
bool containsValues(std::deque<T*>& deque)
{
    bool x = false;
    for (size_t i = 0; i < deque.size(); i++)
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