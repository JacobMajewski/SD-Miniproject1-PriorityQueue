#pragma once
#include "PriorityQueue.hpp"

template <typename T>
class LinkedListQueue : public PriorityQueue<T> {
private:
    struct Node {
        T element;
        int priority;
        Node* next;
        Node(const T& elem, int prio) : element(elem), priority(prio), next(nullptr) {}
    };

    Node* head;
    int count; //size
    void clear();

public:
    LinkedListQueue();
    ~LinkedListQueue();

    void insert(const T& element, int priority) override;
    T extractMax() override;
    T peekMax() const override;
    void modifyKey(const T& element, int newPriority) override;
    int size() const override;
};
