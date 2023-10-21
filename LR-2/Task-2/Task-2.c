#include <stdio.h>
#include <stdbool.h>

#define size 12
#define kol 5

// Функция для проверки, все ли подмножества заполнены или нет
bool checkSum(int sumLeft[], int k)
{
    int res = true;
    for (int i = 0; i < k; i++)
    {
        if (sumLeft[i] != 0) 
        {
            res = false;
        }
    }

    return res;
}

// Вспомогательная функция для решения проблемы с `k` разделами.
// Возвращает true, если существует `k` подмножеств с заданной суммой
bool subsetSum(int S[], int n, int sumLeft[], int A[], int k)
{
    // вернуть true, если найдено подмножество
    if (checkSum(sumLeft, k)) 
    {
        return true;
    }

    // базовый случай: элементов не осталось
    if (n < 0) 
    {
        return false;
    }

    bool result = false;

    // рассматриваем текущий элемент `S[n]` и изучаем все возможности
    // использование поиска с Backtracking
    for (int i = 0; i < k; i++)
    {
        if (!result && (sumLeft[i] - S[n]) >= 0)
        {
            // отметить текущее подмножество элементов
            A[n] = i + 1;

            // добавить текущий элемент в i-е подмножество
            sumLeft[i] = sumLeft[i] - S[n];

            // повторить для оставшихся элементов
            result = subsetSum(S, n - 1, sumLeft, A, k);

            // возврат: удалить текущий элемент из i-го подмножества
            sumLeft[i] = sumLeft[i] + S[n];
        }
    }

    // вернем true, если получим решение
    return result;
}

int accumulate(int S[])
{
    int res = 0;
    for (int i = 0; i < size; i++)
    {
        res += S[i];
    }

    return res;
}

// Функция для решения задачи k-разбиения. Он печатает подмножества, если
// набор `S[0…n-1]` можно разделить на `k` подмножеств с одинаковой суммой
void partition(int S[], int n, int k)
{
    // базовый вариант
    if (n < k)
    {
        printf("k-partition of set S is not possible\n");
        return;
    }

    // получаем сумму всех элементов множества
    int sum = accumulate(S);

    int A[size], sumLeft[kol];

    // создаем массив размером `k` для каждого подмножества и инициализируем его
    // по их ожидаемой сумме, т.е. `sum/k`
    for (int i = 0; i < k; i++) {
        sumLeft[i] = sum / k;
    }

    // вернуть true, если сумма делится на `k` и установить `S` можно
    // разделить на `k` подмножеств с одинаковой суммой
    bool result = !(sum % k) && subsetSum(S, n - 1, sumLeft, A, k);

    if (!result)
    {
        printf("k-partition of set S is not possible\n");
        return;
    }

    // распечатать все k-разделов
    for (int i = 0; i < k; i++)
    {
        printf("Partition %d is ", i);
        for (int j = 0; j < n; j++)
        {
            if (A[j] == i + 1) 
            {
                printf("%d ", S[j]);
            }
        }
        printf("\n");
    }
}

int main()
{
    int S[] = { 7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4 };

    printf("\nOutput: ");

    for (int i = 0; i < size; i++)
    {
        printf("%d ", S[i]);
    }

    printf("\n\n");

    partition(S, size, kol);

    return 0;
}