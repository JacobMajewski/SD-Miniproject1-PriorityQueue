#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <Windows.h>
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

void benchamarks() {
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

int main() {
    int choice = 0;

    while (choice != 1 && choice != 2) {
        std::cout << "Wybierz tryb dzialania:\n";
        std::cout << "(1) Tryb interaktywny (menu uzytkownika)\n";
        std::cout << "(2) Tryb badan (benchmark)\n";
        std::cin >> choice;

        if (choice != 1 && choice != 2)
            std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
    }

    if (choice == 2) {
        benchamarks();
        return 0;
    }

    // Tryb interaktywny
    choice = 0;
    while (choice != 1 && choice != 2) {
        std::cout << "\nWybierz strukture:\n";
        std::cout << "(1) Kolejka na kopcu (HeapQueue)\n";
        std::cout << "(2) Kolejka na liscie jednokierunkowej (LinkedListQueue)\n";
        std::cin >> choice;

        if (choice != 1 && choice != 2)
            std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
    }

    PriorityQueue<int>* queue = nullptr;
    std::string queueType;

    if (choice == 1) {
        queue = new HeapQueue<int>(1000);
        queueType = "HeapQueue";
    }
    else {
        queue = new LinkedListQueue<int>();
        queueType = "LinkedListQueue";
    }

    int element, priority;

    while (true) {
        system("cls");
        std::cout << "--- MENU OPERACJI ---\n";
        std::cout << "Typ kolejki: " << queueType << "\n";
        std::cout << "Rozmiar kolejki: " << queue->size() << "\n\n";

        std::cout << "(1) insert (element, priorytet)\n";
        std::cout << "(2) extract-max\n";
        std::cout << "(3) peek-max\n";
        std::cout << "(4) modify-key (element, nowy priorytet)\n";
        std::cout << "(5) wyjscie\n";
        std::cout << "Wybierz operacje: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Podaj element: ";
            std::cin >> element;
            std::cout << "Podaj priorytet: ";
            std::cin >> priority;
            queue->insert(element, priority);
            break;

        case 2:
            if (queue->size())
                std::cout << "Usunieto: " << queue->extractMax() << "\n";
            else
                std::cout << "Kolejka jest pusta\n";
            break;

        case 3:
            if (queue->size())
                std::cout << "Maksymalny: " << queue->peekMax() << "\n";
            else
                std::cout << "Kolejka jest pusta\n";
            break;

        case 4:
            std::cout << "Podaj element: ";
            std::cin >> element;
            std::cout << "Podaj nowy priorytet: ";
            std::cin >> priority;
            queue->modifyKey(element, priority);
            break;

        case 5:
            std::cout << "Zamykanie programu...\n";
            delete queue;
            return 0;

        default:
            std::cout << "Nieznana opcja, sprobuj ponownie.\n";
        }

        std::cout << "\nNacisnij enter aby kontynuowac...";
        std::cin.ignore();
        std::cin.get();
    }
}