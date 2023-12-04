/*#include <iostream>
#include <thread>
#include <vector>
#include <random>

// Функция, генерирующая случайный символ из ASCII таблицы
char generateRandomChar() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(33, 126);
    return static_cast<char>(dis(gen));
}

// Функция, выполняемая каждым потоком
void threadFunction() {
    char randomChar = generateRandomChar();
    std::cout << randomChar << std::endl;
}

int main() {
    int numThreads = 5; // Заданное количество потоков

    std::vector<std::thread> threads;

    // Создание и запуск потоков
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(threadFunction);
    }

    // Ожидание завершения всех потоков
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}*/


/*
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>
#include <semaphore>
#include <condition_variable>

// Функция, генерирующая случайный символ из ASCII таблицы
char generateRandomChar() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(33, 126);
    return static_cast<char>(dis(gen));
}

// Общие данные для потоков
struct SharedData {
    std::mutex mutex;
    std::condition_variable cv;
    bool ready = false;
};

// Функция, выполняемая каждым потоком
void threadFunction(int id, SharedData& sharedData) {
    // Генерация случайного символа
    char randomChar = generateRandomChar();

    // Захват мьютекса для синхронизации вывода
    std::unique_lock<std::mutex> lock(sharedData.mutex);

    // Ожидание сигнала от основного потока о разрешении вывода
    sharedData.cv.wait(lock, [&sharedData] { return sharedData.ready; });

    // Вывод символа
    std::cout << "Thread " << id << ": " << randomChar << std::endl;

    // Оповещение основного потока о завершении вывода
    sharedData.cv.notify_one();
}

int main() {
    int numThreads = 5; // Заданное количество потоков

    std::vector<std::thread> threads;
    SharedData sharedData;

    // Создание и запуск потоков
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(threadFunction, i, std::ref(sharedData));
    }

    // Задержка перед началом вывода
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Разрешение вывода символов
    {
        std::lock_guard<std::mutex> lock(sharedData.mutex);
        sharedData.ready = true;
        sharedData.cv.notify_all();
    }

    // Ожидание завершения вывода всех символов
    {
        std::unique_lock<std::mutex> lock(sharedData.mutex);
        sharedData.cv.wait(lock, [&sharedData, numThreads] { return !sharedData.ready; });
    }

    // Ожидание завершения всех потоков
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}*/