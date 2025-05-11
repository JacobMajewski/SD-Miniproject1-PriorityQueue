#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include "HeapQueue.cpp"
#include "LinkedListQueue.cpp"

template <typename QueueType>
long long measureOperation(QueueType& queue, const std::string& operation, int element, int priority) {
    auto start = std::chrono::high_resolution_clock::now();

    if (operation == "insert") {
        queue.insert(element, priority);
    }
    else if (operation == "extract-max") {
        queue.extractMax();
    }
    else if (operation == "peek") {
        queue.peekMax();
    }
    else if (operation == "modify-key") {
        queue.modifyKey(element, priority);
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

template <typename QueueType>
void prepareQueue(QueueType& queue, int size, std::mt19937 genP, std::mt19937 genC) {
    std::uniform_int_distribution<int> distToFill(0, size * 1000);
    for (int i = 0; i < size; i++) {
        queue.insert(distToFill(genC), distToFill(genP));
    }
}
template <typename T>
void prepareQueue(HeapQueue<T>& queue, int size, std::mt19937 genP, std::mt19937 genC) {
    std::uniform_int_distribution<int> distToFill(0, size * 1000);
    T* elements = new T[size];
    int* priorities = new int[size];
    for (int i = 0; i < size; i++) {
        elements[i] = distToFill(genC);
        priorities[i] = distToFill(genP);
    }
        queue.fastBuilder(elements, priorities);
    delete[] elements;
    delete[] priorities;
}

int main() {
    const std::string OPERATIONS[] = { "insert", "extract-max", "peek", "modify-key" };
    const int SIZES[] = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };

    const int NUM_SEEDS = 25;
    const int BASE_SEED = 14052003;

    int PRIORITY_SEEDS[NUM_SEEDS];
    int CONTENT_SEEDS[NUM_SEEDS];

    std::mt19937 gen(BASE_SEED);
    std::uniform_int_distribution<int> dist(0, 1000000);
    for (int i = 0; i < NUM_SEEDS; i++) {
        PRIORITY_SEEDS[i] = dist(gen);
        CONTENT_SEEDS[i] = dist(gen);
    }

    std::ofstream heapFile("HeapQueue.csv");
    std::ofstream listFile("LinkedListQueue.csv");

    heapFile << "size,operation,average_time_ns\n";
    listFile << "size,operation,average_time_ns\n";

    for (int size : SIZES) {
        for (const std::string& operation : OPERATIONS) {
            long long heapSum = 0;
            long long listSum = 0;

            for (int seedIdx = 0; seedIdx < NUM_SEEDS; seedIdx++) {
                std::mt19937 genP(PRIORITY_SEEDS[seedIdx]);
                std::mt19937 genC(CONTENT_SEEDS[seedIdx]);
                HeapQueue<int> heap(size);
                LinkedListQueue<int> list;

                prepareQueue(heap, size, genP, genC);
                prepareQueue(list, size, genP, genC);
                int newElement = dist(genC);
                int newPriority = dist(genP);
                heapSum += measureOperation(heap, operation, newElement, newPriority);
                listSum += measureOperation(list, operation, newElement, newPriority);
            }

            heapFile << size << "," << operation << "," << (heapSum / NUM_SEEDS) << "\n";
            listFile << size << "," << operation << "," << (listSum / NUM_SEEDS) << "\n";
        }
    }

    heapFile.close();
    listFile.close();

    std::cout << "Dane zapisane do HeapQueue.csv i LinkedListQueue.csv\n";
}
