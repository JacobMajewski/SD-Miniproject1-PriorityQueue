#pragma once
template <typename T>
class PriorityQueue {
public:
    //  Dodanie elementu e o priorytecie p  
    virtual void insert(const T& element, int priority) = 0;

    //  Usuni�cie i zwr�cenie elementu o najwi�kszym priorytecie  
    virtual T extractMax() = 0;

    //  Zwr�cenie (podejrzenie) elementu o najwi�kszym priorytecie  
    virtual T peekMax() const = 0;

    //  Zmiana priorytetu elementu e na p. Mo�na podzieli� na operacje decrease-key oraz increase-key.  
    virtual void modifyKey(const T& element, int newPriority) = 0;

    //  Zwr�cenie rozmiaru.  
    virtual int size() const = 0;

    virtual ~PriorityQueue() {}
};