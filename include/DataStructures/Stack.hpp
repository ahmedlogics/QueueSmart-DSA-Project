#pragma once
#include "LinkedList.hpp"

template <typename T>
class Stack {
    LinkedList<T> list;
public:

    void push(T data) { list.insert_front(data); }

    
    T pop() { return list.remove_from_front(); }


    T top() { 
        if (list.isEmpty()) throw std::out_of_range("Stack empty");
        return list.get_head()->data; 
    }

    bool isEmpty() const { return list.isEmpty(); }
};