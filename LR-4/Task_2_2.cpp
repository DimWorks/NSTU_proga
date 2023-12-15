#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

mutex mtx;

void printDate(Date date) {
    lock_guard<mutex> guard(mtx);
    cout << date.day << "/" << date.month << "/" << date.year << endl;
}

void findDatesInRange(Date D1, Date D2) {
    if (D2.year < D1.year || (D2.year == D1.year && D2.month < D1.month) || (D2.year == D1.year && D2.month == D1.month && D2.day < D1.day)) {
        cout << "Invalid date range" << endl;
        return;
    }

    Date currentDate = D1;
    while (currentDate.year < D2.year || (currentDate.year == D2.year && currentDate.month < D2.month) || (currentDate.year == D2.year && currentDate.month == D2.month && currentDate.day <= D2.day)) {
        thread t(printDate, currentDate);
        t.join();
        if (currentDate.day == 31 && (currentDate.month == 1 || currentDate.month == 3 || currentDate.month == 5 || currentDate.month == 7 || currentDate.month == 8 || currentDate.month == 10 || currentDate.month == 12)) {
            currentDate.day = 1;
            if (currentDate.month == 12) {
                currentDate.month = 1;
                currentDate.year++;
            }
            else {
                currentDate.month++;
            }
        }
        else if (currentDate.day == 30 && (currentDate.month == 4 || currentDate.month == 6 || currentDate.month == 9 || currentDate.month == 11)) {
            currentDate.day = 1;
            currentDate.month++;
        }
        else if (currentDate.day == 28 && currentDate.month == 2 && ((currentDate.year % 4 != 0) || (currentDate.year % 100 == 0 && currentDate.year % 400 != 0))) {
            currentDate.day = 1;
            currentDate.month++;
        }
        else if (currentDate.day == 29 && currentDate.month == 2) {
            currentDate.day = 1;
            currentDate.month++;
        }
        else {
            currentDate.day++;
        }
    }
}

int main() {
    Date D1 = { 21, 5, 2001 };
    Date D2 = { 1, 1, 2024 };
    auto start = chrono::high_resolution_clock::now(); // Засекаем время 
    findDatesInRange(D1, D2);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Elapsed time with semaphore: " << elapsed.count() << " s" << endl;


    return 0;
}
