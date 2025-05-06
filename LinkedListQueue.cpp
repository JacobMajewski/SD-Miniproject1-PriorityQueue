#include "LinkedListQueue.hpp"
#include <stdexcept>

template <typename T>
LinkedListQueue<T>::LinkedListQueue() : head(nullptr), count(0) {}

template <typename T>
LinkedListQueue<T>::~LinkedListQueue() {
    clear();
}

template <typename T>
void LinkedListQueue<T>::insert(const T& element, int priority) {
    Node* newNode = new Node(element, priority);
    if (!head || priority > head->priority) {
        newNode->next = head;
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next && current->next->priority >= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    ++count;
}

template <typename T>
T LinkedListQueue<T>::extractMax() {
    if (!head) throw std::runtime_error("Kolejka jest pusta");
    Node* temp = head;
    T result = head->element;
    head = head->next;
    delete temp;
    --count;
    return result;
}

template <typename T>
T LinkedListQueue<T>::peekMax() const {
    if (!head) throw std::runtime_error("Kolejka jest pusta");
    return head->element;
}

template <typename T>
void LinkedListQueue<T>::modifyKey(const T& element, int newPriority) {
    Node* prev = nullptr;
    Node* current = head;

    //znalezienie wiezu
    while (current && !(current->element == element)) {
        prev = current;
        current = current->next;
    }

    if (!current) return;//gdy brak elementy

    //usuwanie wezlu
    if (prev) {
        prev->next = current->next;
    }
    else {
        head = current->next;
    }
    --count;

    //dodanie z nowymn priorytetem
    insert(element, newPriority);

    delete current;
}

template <typename T>
int LinkedListQueue<T>::size() const {
    return count;
}

template <typename T>
void LinkedListQueue<T>::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
}
