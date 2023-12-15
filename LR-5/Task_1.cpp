#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Базовый класс для зверей
class Animal {
protected:
    int x; // Координата x
    int y; // Координата y
    int direction; // Направление движения (0 - вверх, 1 - вправо, 2 - вниз, 3 - влево)
    int age; // Возраст

public:
    Animal(int startX, int startY) : x(startX), y(startY), direction(rand() % 4), age(0) {}

    virtual void move(int fieldWidth, int fieldHeight) = 0; // Виртуальный метод движения

    void changeDirection() {
        direction = (direction + 1) % 4;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    int getAge() const {
        return age;
    }

    void incrementAge() {
        age++;
    }
};

// Подкласс для хищников
class Predator : public Animal {
public:
    bool isAte;/// = false;
    Predator(int startX, int startY) : Animal(startX, startY) {}

    void move(int fieldWidth, int fieldHeight) override {
        switch (direction) {
        case 0: // Вверх
            y = (y - 2 + fieldHeight) % fieldHeight;
            break;
        case 1: // Вправо
            x = (x + 2) % fieldWidth;
            break;
        case 2: // Вниз
            y = (y + 2) % fieldHeight;
            break;
        case 3: // Влево
            x = (x - 2 + fieldWidth) % fieldWidth;
            break;
        }
    }

    int getMaxAge()
    {
        return 15;
    }
};

// Подкласс для жертв
class Prey : public Animal {
private:
   // const int maxAge = 11;
public:
    Prey(int startX, int startY) : Animal(startX, startY) {}

    void move(int fieldWidth, int fieldHeight) override {
        switch (direction) {
        case 0: // Вверх
            y = (y - 1 + fieldHeight) % fieldHeight;
            break;
        case 1: // Вправо
            x = (x + 1) % fieldWidth;
            break;
        case 2: // Вниз
            y = (y + 1) % fieldHeight;
            break;
        case 3: // Влево
            x = (x - 1 + fieldWidth) % fieldWidth;
            break;
        }
    }

    int getMaxAge()
    {
        return 11;
    }
};

// Функция для вывода данных поля в виде таблицы на каждом ходе
void printField(
    const vector<Predator>& predators, 
    const vector<Prey>& prey, 
    int fieldWidth, 
    int fieldHeight, 
    int move) 
{
    cout << endl << "A move: " << move << endl;


    for (int i = 0; i < fieldHeight; i++) 
    {
        for (int j = 0; j < fieldWidth; j++) 
        {
            bool printedAnimal = false;

            // Проверяем наличие хищника на текущей клетке и выводим его на экран
            for (const auto& predator : predators) 
            {
                if (predator.getX() == j && predator.getY() == i) 
                {
                    cout << "X(" << predator.getAge() << ")";
                    printedAnimal = true;
                    break;
                }
            }

            // Проверяем наличие жертвы на текущей клетке и выводим ее на экран
            if (!printedAnimal) 
            {
                for (const auto& preyAnimal : prey) 
                {
                    if (preyAnimal.getX() == j && preyAnimal.getY() == i) 
                    {
                        cout << "Z(" << preyAnimal.getAge() << ")";
                        printedAnimal = true;
                        break;
                    }
                }
            }

            if (!printedAnimal) 
            {
                cout << "*";
            }

            cout << "\t";
        }

        cout << endl;
    }
}

int main() 
{
    srand(time(0)); // Инициализация генератора случайных чисел

    int fieldWidth, fieldHeight, numMoves, numPredators, munPrey;
    cout << "Enter the dimensions of the field (width and height): ";
    cin >> fieldWidth >> fieldHeight;
    cout << "Enter the number of moves: ";
    cin >> numMoves;
    cout << "Enter the number of animals(predators and prey): ";
    cin >> numPredators >> munPrey;

    vector<Predator> predators; // Хищники
    vector<Prey> prey; // Жертвы

    // Генерация начальных координат и направлений движения для хищников
    for (int i = 0; i < numPredators; i++)
    {
        Predator predator(rand() % fieldWidth, rand() % fieldHeight);
        predator.isAte = false;
        predators.push_back(predator);
    }

    // Генерация начальных координат и направлений движения для жертв
    for (int i = 0; i < munPrey; i++)
    {
        Prey preyAnimal(rand() % fieldWidth, rand() % fieldHeight);
        prey.push_back(preyAnimal);
    }

    // Цикл по количеству ходов
    for (int i = 0; i < numMoves; i++) 
    {

        
        // Движение хищников
        if (predators.size() != 0)
        {
            for (auto predator = predators.begin(); predator != predators.end();)
            {

                predator->move(fieldWidth, fieldHeight);

                if ((i + predator->getX() + predator->getY()) % 5 == 0)
                { // Каждый пятый ход меняем направление движения хищника
                    predator->changeDirection();
                }
                predator->incrementAge();

                if (predator->getAge() == predator->getMaxAge())
                {
                    predator = predators.erase(predator);
                }
                else
                {
                    predator++;
                }
            }
        }
        
        vector<Prey> childPrey;

        // Движение жертв
        for (auto preyAnimal = prey.begin(); preyAnimal != prey.end();) 
        {
            preyAnimal->move(fieldWidth, fieldHeight);

            if ((i + preyAnimal->getX() + preyAnimal->getY()) % 3 == 0) 
            { // Каждый третий ход меняем направление движения жертвы
                preyAnimal->changeDirection();
            }
            preyAnimal->incrementAge();

            if (preyAnimal->getAge() == preyAnimal->getMaxAge())
            {
                preyAnimal = prey.erase(preyAnimal);
            }
            else if (preyAnimal->getAge() == 5 || preyAnimal->getAge() == 10)
            {
                Prey tmp(rand() % fieldWidth, rand() % fieldHeight);
                childPrey.push_back(tmp);
            }
            else
            {
                preyAnimal++;
            }

        }

        prey.insert(prey.end(), childPrey.begin(), childPrey.end());
        childPrey.clear();


        vector<Predator> childPredator;

        // Проверка наличия хищника на одной клетке с жертвой и съедание жертвы
        for (auto itPredator = predators.begin(); itPredator != predators.end(); itPredator++) 
        {
            for (auto itPrey = prey.begin(); itPrey != prey.end(); itPrey++) 
            {
                if (itPredator->getX() == itPrey->getX() && itPredator->getY() == itPrey->getY()) 
                {
                    prey.erase(itPrey);
                    if (itPredator->isAte)
                    {
                        Predator tmp(itPredator->getX(), itPredator->getY());
                        tmp.isAte = false;
                        childPredator.push_back(tmp);

                        itPredator->isAte = false;
                    }
                    else
                    {
                        itPredator->isAte = true;
                    }
                    break;
                }
            }
        }


        predators.insert(predators.end(), childPredator.begin(), childPredator.end());
        childPredator.clear();

        printField(predators, prey, fieldWidth, fieldHeight, i+1); // Вывод данных поля на экран после каждого хода
    }
}