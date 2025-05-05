#pragma once
template <typename T>
class PriorityQueue {
public:
    //  Dodanie elementu e o priorytecie p  
    virtual void insert(const T& element, int priority) = 0;

    //  Usuniêcie i zwrócenie elementu o najwiêkszym priorytecie  
    virtual T extractMax() = 0;

    //  Zwrócenie (podejrzenie) elementu o najwiêkszym priorytecie  
    virtual T peekMax() const = 0;

    //  Zmiana priorytetu elementu e na p. Mo¿na podzieliæ na operacje decrease-key oraz increase-key.  
    virtual void modifyKey(const T& element, int newPriority) = 0;

    //  Zwrócenie rozmiaru.  
    virtual int size() const = 0;

    virtual ~PriorityQueue() {}
};