#pragma once
#include "LinkedList.hpp"

template <typename T>
class Queue {
    LinkedList<T> list;
public:

    void enqueue(T data) { list.insert_end(data); }
    

    T dequeue() { return list.remove_from_front(); }
    
    
    void enqueue_front(T data) { list.insert_front(data); } //for undo

    bool isEmpty() const { return list.isEmpty(); }
    auto get_head() const { return list.get_head(); }
};