#include "HeapQueue.hpp"

template <typename T>
HeapQueue<T>::HeapQueue(int initialCapacity)
    : capacity(initialCapacity), count(0)
{
    heap = new Node[capacity];
}

template <typename T>
HeapQueue<T>::~HeapQueue() {
    delete[] heap;
}

template <typename T>
void HeapQueue<T>::resize() {
    capacity *= 2;
    Node* newHeap = new Node[capacity];
    for (int i = 0; i < count; ++i) 
    {
        newHeap[i] = heap[i];
    }

    delete[] heap;
    heap = newHeap;
}

template <typename T>
void HeapQueue<T>::swapNodes(Node& a, Node& b) {
    Node temp = a;
    a = b;
    b = temp;
}

template <typename T>
void HeapQueue<T>::heapifyUp(int index) {
    while (index > 0) {

        int parent = (index - 1) / 2;
        if (heap[index].priority <= heap[parent].priority)
            break;

        swapNodes(heap[index], heap[parent]);
        index = parent;
    }
}

template <typename T>
void HeapQueue<T>::heapifyDown(int index) {
    int left, right, largest;
    while (true) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        largest = index;

        if (left < count && heap[left].priority > heap[largest].priority) largest = left;
        if (right < count && heap[right].priority > heap[largest].priority) largest = right;

        if (largest == index) break;

        swapNodes(heap[index], heap[largest]);
        index = largest;
    }
}

template <typename T>
int HeapQueue<T>::findIndex(const T& element) const {
    for (int i = 0; i < count; ++i) {
        if (heap[i].element == element) return i;
    }
    return -1;
}

template <typename T>
void HeapQueue<T>::insert(const T& element, int priority) {
    if (count == capacity) {
        resize();
    }
    heap[count] = Node{ element, priority };
    heapifyUp(count);
    ++count;
}

template <typename T>
T HeapQueue<T>::extractMax() {
    if (count == 0) {
        throw std::out_of_range("HeapQueue is empty");
    }
    T maxElem = heap[0].element;
    heap[0] = heap[count - 1];
    --count;
    if (count > 0) {
        heapifyDown(0);
    }
    return maxElem;
}

template <typename T>
T HeapQueue<T>::peekMax() const {
    if (count == 0) {
        throw std::out_of_range("HeapQueue is empty");
    }
    return heap[0].element;
}

template <typename T>
void HeapQueue<T>::modifyKey(const T& element, int newPriority) {
    int index = findIndex(element);
    if (index == -1) {
        throw std::invalid_argument("Element not found in HeapQueue");
    }
    int oldPriority = heap[index].priority;
    heap[index].priority = newPriority;
    if (newPriority > oldPriority) {
        heapifyUp(index);
    }
    else if (newPriority < oldPriority) {
        heapifyDown(index);
    }
}

template <typename T>
int HeapQueue<T>::size() const {
    return count;
}
