#include "LinkedListQueue.hpp"
#include <stdexcept>

template <typename T>
LinkedListQueue<T>::LinkedListQueue() : head(nullptr), tail(nullptr), count(0) {}


template <typename T>
LinkedListQueue<T>::~LinkedListQueue() {
    clear();
}
// same priority -> FIFO
template <typename T>
void LinkedListQueue<T>::insert(const T& element, int priority) {
    Node* newNode = new Node(element, priority);

    // Jeœli lista jest pusta lub nowy ma wiêkszy priorytet ni¿ head
    if (!head || priority > head->priority) {
        newNode->next = head;
        head = newNode;
        if (!tail) tail = newNode; // pierwszy element
    }
    // Jeœli nowy element ma najni¿szy priorytet (czyli idzie na koniec)
    else if (!head->next || priority <= tail->priority) {
        tail->next = newNode;
        tail = newNode;
    }
    else {
        Node* current = head;
        while (current->next && current->next->priority >= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        if (!newNode->next) tail = newNode; // aktualizacja tail jeœli na koñcu
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

    if (!head) tail = nullptr; // jeœli usunêliœmy ostatni element

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

    // Znalezienie pasuj¹cego wêz³a
    while (current && !(current->element == element)) {
        prev = current;
        current = current->next;
    }

    if (!current) return; // element nie znaleziony

    // Usuniêcie elementu
    if (prev) prev->next = current->next;
    else head = current->next;

    if (!current->next) tail = prev;
    delete current;
    --count;

    // Dodanie z nowym priorytetem
    insert(element, newPriority);
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
    head = tail = nullptr;
    count = 0;
}
