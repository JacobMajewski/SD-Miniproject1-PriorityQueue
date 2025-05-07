#include "HeapQueue.hpp"

template <typename T>
HeapQueue<T>::HeapQueue(int initialCapacity) : capacity(initialCapacity), count(0)
{
    //to be done
}

template <typename T>
HeapQueue<T>::~HeapQueue() {
    //to be done
}

template <typename T>
void HeapQueue<T>::resize() {
    //to be done
}

template <typename T>
void HeapQueue<T>::swapNodes(Node& a, Node& b) {
    Node temp = a;
    a = b;
    b = temp;
}

template <typename T>
void HeapQueue<T>::heapifyUp(int index) {
    //to be done
    }
}

template <typename T>
void HeapQueue<T>::heapifyDown(int index) {
    int left, right, largest;
    while (true) {
        //to be done
    }
}

template <typename T>
int HeapQueue<T>::findIndex(const T& element) const {
    //to be done
}

template <typename T>
void HeapQueue<T>::insert(const T& element, int priority) {
    //to be done
}

template <typename T>
T HeapQueue<T>::extractMax() {
    //to be done
}

template <typename T>
T HeapQueue<T>::peekMax() const {
    //to be done
}

template <typename T>
void HeapQueue<T>::modifyKey(const T& element, int newPriority) {
//to be done
}

template <typename T>
int HeapQueue<T>::size() const {
    return count;
}
