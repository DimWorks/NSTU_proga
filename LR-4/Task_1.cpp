#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include <semaphore>
#include <condition_variable>
#include <atomic>

using namespace std;

mutex testMutex;
condition_variable cv;

binary_semaphore testSemaphore(1); // Используем бинарный семафор

bool ready = false;

class Barrier {
public:
    explicit Barrier(size_t count) : threshold(count), count(count), generation(0) {}

    void wait() {
        unique_lock<mutex> lock{ myMutex };
        auto lgen = generation;
        if (--count == 0) {
            generation++;
            count = threshold;
            cond.notify_all();
        }
        else {
            cond.wait(lock, [this, lgen] { return lgen != generation; });
        }
    }

private:
    mutex myMutex;
    condition_variable cond;
    size_t threshold;
    size_t count;
    size_t generation;
};

class SpinLock {
private:
    atomic_flag flag = ATOMIC_FLAG_INIT; // Используем атомарный флаг для реализации спинлока
public:
    void lock() {
        while (flag.test_and_set(memory_order_acquire)) {} // Пытаемся установить флаг, ожидая освобождения
    }

    void unlock() {
        flag.clear(memory_order_release); // Освобождаем флаг
    }
};

class SpinWait {
private:
    atomic_flag flag = ATOMIC_FLAG_INIT; // Используем атомарный флаг для реализации спинлока
public:
    void lock() 
    {
        while (flag.test_and_set(memory_order_acquire)) 
        {
            while (flag.test(memory_order_relaxed)) 
            {
                this_thread::yield(); // Spin-wait пока флаг не освободится
            }
        } // Пытаемся установить флаг, ожидая освобождения
    }

    void unlock() {
        flag.clear(memory_order_release); // Освобождаем флаг
    }
};

// Функция, генерирующая случайный символ из ASCII таблицы
char generateRandomChar() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(33, 126);
    return static_cast<char>(dis(gen));
}


void cleanRace()
{
    cout << generateRandomChar() << " ";
}

void useMutex()
{
    testMutex.lock();

    cout << generateRandomChar() << " ";

    testMutex.unlock();
}

void useSemaphore()
{
    testSemaphore.acquire();

    cout << generateRandomChar() << " ";

    testSemaphore.release();
}

void useBarrier(Barrier& barrier)
{
    cout << generateRandomChar() << " ";

    barrier.wait();
}

void useMonitor()
{
    unique_lock<mutex> lock(testMutex);
        // ждем, пока не будет готов ресурс
        cv.wait(lock, [] { return ready; });
        // работаем с ресурсом
    cout << generateRandomChar() << " ";
}

void startMonitor() {
    {
        lock_guard<mutex> lock(testMutex);
        // подготавливаем ресурс
        ready = true;
    }
    cv.notify_one();
}



void useSpinLock(SpinLock& spinlock)
{
    spinlock.lock();

    cout << generateRandomChar() << " ";

    spinlock.unlock();
}



void useSpinWait(SpinWait& spinwait)
{
    spinwait.lock();

    cout << generateRandomChar() << " ";

    spinwait.unlock();
}

int main()
{
    vector<thread> threads;
    int num = 35;
    srand((unsigned int)time(0));

    //-----------------------------Чистая гонка за ресурсы-------------------------------

    auto startCleanRace = chrono::high_resolution_clock::now(); // Засекаем время 
    for (int i = 0; i < num; i++)
    {
        threads.push_back(thread(cleanRace));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    cout << endl;

    threads.clear();

    auto endCleanRace = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedCleanRace = endCleanRace - startCleanRace;
    cout << "Elapsed time without any one: " << elapsedCleanRace.count() << " s" << endl;

    //-------------------------Используем мьютекс-----------------------------------------

    auto startWithMutex = chrono::high_resolution_clock::now(); // Засекаем время 

    for (int i = 0; i < num; i++)
    {
        threads.push_back(thread(useMutex));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    cout << endl;

    threads.clear();

    auto endWithMutex = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedWithMutex = endWithMutex - startWithMutex;
    cout << "Elapsed time with mutex: " << elapsedWithMutex.count() << " s" << endl;


    //--------------------------------Используем семафоры----------------------------------
    auto startWithSemaphore = chrono::high_resolution_clock::now(); // Засекаем время 

    for (int i = 0; i < num; i++)
    {
        threads.push_back(thread(useSemaphore));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    cout << endl;

    threads.clear();

    auto endWithSemaphore = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedWithSemaphore = endWithSemaphore - startWithSemaphore;
    cout << "Elapsed time with semaphore: " << elapsedWithSemaphore.count() << " s" << endl;


    //------------------------------Используем барьеры------------------------------------

    auto startWithBarrier = chrono::high_resolution_clock::now(); // Засекаем время 
    Barrier barrier(num);

    for (int i = 0; i < num; i++)
    {
        threads.emplace_back(thread(useBarrier, ref(barrier)));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    cout << endl;

    threads.clear();

    auto endWithBarrier = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedWithBarrier = endWithBarrier - startWithBarrier;
    cout << "Elapsed time with Barrier: " << elapsedWithBarrier.count() << " s" << endl;

    //------------------------------Используем монитор------------------------------------

    auto startWithMonitor = chrono::high_resolution_clock::now(); // Засекаем время 

    for (int i = 0; i < num; i++)
    {
        threads.emplace_back(thread(useMonitor));
    }

    for (auto& t : threads)
    {
        startMonitor();
        t.join();
    }

    cout << endl;

    threads.clear();

    auto endWithMonitor = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedWithMonitor = endWithMonitor - startWithMonitor;
    cout << "Elapsed time with Monitor: " << elapsedWithMonitor.count() << " s" << endl;


    //----------------------------Используем SpinLock------------------------------------

    auto startWithSpinLock = chrono::high_resolution_clock::now(); // Засекаем время 
   
    SpinLock spinlock;

    for (int i = 0; i < num; i++)
    {
        threads.emplace_back(thread(useSpinLock, ref(spinlock)));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    cout << endl;

    threads.clear();

    auto endWithSpinLock = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedWithSpinLock = endWithSpinLock - startWithSpinLock;
    cout << "Elapsed time with SpinLock: " << elapsedWithSpinLock.count() << " s" << endl;

    //----------------------------Используем SpinWait------------------------------------

    auto startWithSpinWait = chrono::high_resolution_clock::now(); // Засекаем время 

    SpinWait spinwait;

    for (int i = 0; i < num; i++)
    {
        threads.emplace_back(thread(useSpinWait, ref(spinwait)));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    cout << endl;

    threads.clear();

    auto endWithSpinWait = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedWithSpinWait = endWithSpinWait - startWithSpinWait;
    cout << "Elapsed time with SpinWait: " << elapsedWithSpinWait.count() << " s" << endl;

    return 0;
}