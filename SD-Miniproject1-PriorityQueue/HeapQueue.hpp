#pragma once
#include "PriorityQueue.hpp"

template <typename T>
class HeapQueue : public PriorityQueue<T> {
private:
    struct Node {
        T element;
        int priority;
    };

    Node* heap;    //wskaznik na tabele dynamiczn¹
    int capacity; // pojemnoœæ tablicy
    int count;   //  liczba elementów w tablicy

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();
    int findIndex(const T& element) const;
    void swapNodes(Node& a, Node& b); //do zamiany elementow, bo nie chcialem uzywac std swap // ok :)

public:
    HeapQueue(int initialCapacity = 16); // i wont question that
    ~HeapQueue();

    void insert(const T& element, int priority) override;
    T extractMax() override;
    T peekMax() const override;
    void modifyKey(const T& element, int newPriority) override;
    int size() const override;
};