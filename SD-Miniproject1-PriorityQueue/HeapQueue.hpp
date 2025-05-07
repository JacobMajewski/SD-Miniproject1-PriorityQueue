#pragma once
#include "PriorityQueue.hpp"
#include <stdexcept>

template <typename T>
class HeapQueue : public PriorityQueue<T> {
private:
    struct Node {
        T element;
        int priority;
    };

    Node* heap; //wsk na tab
    int capacity; //pojemnosc
    int count; //liczba elementow

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();
    int findIndex(const T& element) const;
    void swapNodes(Node& a, Node& b);//do zamiany elementow, bo nie chcialem uzywac std swap

public:
    HeapQueue(int initialCapacity = 16);
    ~HeapQueue();

    void insert(const T& element, int priority) override;
    T extractMax() override;
    T peekMax() const override;
    void modifyKey(const T& element, int newPriority) override;
    int size() const override;
};
