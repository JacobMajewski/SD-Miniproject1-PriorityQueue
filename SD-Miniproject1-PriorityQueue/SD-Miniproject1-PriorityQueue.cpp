#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include "HeapQueue.cpp"
#include "LinkedListQueue.cpp"

template <typename QueueType>
long long measureOperation(QueueType& queue, const std::string& operation) {
    auto start = std::chrono::high_resolution_clock::now();

    if (operation == "insert") {
        queue.insert(42, 100);
    }
    else if (operation == "extract-max") {
        queue.extractMax();
    }
    else if (operation == "peek") {
        queue.peekMax();
    }
    else if (operation == "modify-key") {
        queue.modifyKey(42, 200);
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

template <typename QueueType>
void prepareQueue(QueueType& queue, int size, int prioritySeed, int contentSeed) {
    std::mt19937 genP(prioritySeed);
    std::mt19937 genC(contentSeed);
    std::uniform_int_distribution<int> distToFill(0, size * 1000);
    for (int i = 0; i < size; i++) {
        queue.insert(distToFill(genC), distToFill(genP));
    }
}

int main() {
    const std::string OPERATIONS[] = { "insert", "extract-max", "peek", "modify-key" };
    const int SIZES[] = { 500000};
    //const int SIZES[] = { 5000, 10000, 20000, 50000, 100000, 200000, 500000 };

    const int NUM_SEEDS = 100;
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
                HeapQueue<int> heap(size);
                LinkedListQueue<int> list;

                prepareQueue(heap, size, PRIORITY_SEEDS[seedIdx], CONTENT_SEEDS[seedIdx]);
                prepareQueue(list, size, PRIORITY_SEEDS[seedIdx], CONTENT_SEEDS[seedIdx]);

                heapSum += measureOperation(heap, operation);
                listSum += measureOperation(list, operation);
            }

            heapFile << size << "," << operation << "," << (heapSum / NUM_SEEDS) << "\n";
            listFile << size << "," << operation << "," << (listSum / NUM_SEEDS) << "\n";
        }
    }

    heapFile.close();
    listFile.close();

    std::cout << "Dane zapisane do HeapQueue.csv i LinkedListQueue.csv\n";
}
