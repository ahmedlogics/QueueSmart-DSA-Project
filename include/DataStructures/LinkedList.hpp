#pragma once
#include <stdexcept>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int currentSize;

public:
    LinkedList() : head(nullptr), tail(nullptr), currentSize(0) {}

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    
    void insert_end(T data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        currentSize++;
    }

    
    void insert_front(T data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        currentSize++;
    }

    // For Queue (Dequeue) AND Stack (Pop)
    T remove_from_front() {
        if (isEmpty()) throw std::out_of_range("List is empty");
        
        Node* temp = head;
        T data = head->data;
        head = head->next;
        
        if (head == nullptr) tail = nullptr;
        
        delete temp;
        currentSize--;
        return data;
    }

    Node* get_head() const { return head; }
    bool isEmpty() const { return head == nullptr; }
    int getSize() const { return currentSize; }
};