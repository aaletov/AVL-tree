#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <deque>

template < class Key, class T >
bool containsValues(std::deque<T*>& deque);

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