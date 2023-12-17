#include <iostream>

#define MAX 20

using namespace std;

class bankers
{
private:
    int al[MAX][MAX], m[MAX][MAX], n[MAX][MAX], avail[MAX];
    int num_process, num_thread, k, result[MAX], pnum, work[MAX];
    bool finish[MAX];

public:
    bankers();
    void input();
    void letEatBee();
    int search(int);
    void output();
};

bankers::bankers()
{
    k = 0;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            al[i][j] = 0;
            m[i][j] = 0;
            n[i][j] = 0;
        }
        avail[i] = 0;
        result[i] = 0;
        finish[i] = false;
    }
}

void bankers::input()
{
    int i, j;
    cout << "Enter number of processes: ";
    cin >> num_process;
    cout << "Enter number of threads: ";
    cin >> num_thread;

    //-------------------------------Заполняем колонок (Выделено)------------------------------------

    cout << "Enter allocated threads for every process: " << endl;
    for (i = 0; i < num_process; i++)
    {
        cout << "\nProcess " << i;
        for (j = 0; j < num_thread; j++)
        {
            cout << "\nThread " << j << ": ";
            cin >> al[i][j];
        }
    }

    //-----------------------------Заполнение колонок (Максимум)-------------------------------------

    cout << "Enter maximum threads that are needed for every process: " << endl;
    for (i = 0; i < num_process; i++)
    {
        cout << "\nProcess " << i;
        for (j = 0; j < num_thread; j++)
        {
            cout << "\nThread " << j << ": ";
            cin >> m[i][j];
            n[i][j] = m[i][j] - al[i][j];
        }
    }

    //-----------------------------Заполняем колонки (Доступно)--------------------------------------

    cout << "Enter currently available threads in the system: " << endl;
    for (j = 0; j < num_thread; j++)
    {
        cout << "Thread " << j << ": ";
        cin >> avail[j];
        work[j] = -1;
    }
}

void bankers::letEatBee()
{
    int i = 0, j;
    bool flag;
    while (1)
    {
        if (!finish[i])
        {
            pnum = search(i);
            if (pnum != -1)
            {
                result[k++] = i;
                finish[i] = true;
                for (j = 0; j < num_thread; j++)
                {
                    avail[j] = avail[j] + al[i][j];
                }
            }
        }

        i++;

        if (i == num_process)
        {
            flag = false;
            for (j = 0; j < num_thread; j++)
            {
                if (avail[j] != work[j])
                {
                    flag = true;
                }       
            }

            for (j = 0; j < num_thread; j++)
            {
                work[j] = avail[j];
            }               

            if (!flag)
            {
                break;
            }               
            else
            {
                i = 0;
            }               
        }
    }
}

int bankers::search(int i)
{
    int j;
    for (j = 0; j < num_thread; j++)
    {
        if (n[i][j] > avail[j])
        {
            return -1;
        }
    }

    return 0;
}

void bankers::output()
{
    int i, j;
    cout << endl << "\tOUTPUT:" << endl;
    cout << endl << "PROCESS\t ALLOTED\t MAXIMUM\t NEED";
    for (i = 0; i < num_process; i++)
    {
        cout << "\nP" << i << "\t ";
        for (j = 0; j < num_thread; j++)
        {
            cout << al[i][j] << " ";
        }
        cout << "\t\t";
        for (j = 0; j < num_thread; j++)
        {
            cout << m[i][j] << " ";
        }
        cout << " " << "\t\t";
        for (j = 0; j < num_thread; j++)
        {
            cout << n[i][j] << " ";
        }
    }
    cout << "\nThe sequence of the safe processes are: \n";
    for (i = 0; i < k; i++)
    {
        int temp = result[i];
        cout << "P" << temp << " -> ";
    }
    cout << "\nThe sequence of unsafe processes are: \n";

    bool isSave = false;

    for (i = 0; i < num_process; i++)
    {
        if (!finish[i])
        {
            isSave = true;
        }
        cout << "P" << i << " -> ";
    }
    cout << endl << "RESULT:";
    if (isSave)
    {
        cout <<"WRNING: The system is in an unsafe state, and mutual blocking may occur" << endl;
    }       
    else
    {
        cout << "The system is in a safe state, and mutual blocking cannot occur" << endl;
    }       
}

int main()
{
    bankers BankMan;
    BankMan.input();
    BankMan.letEatBee();
    BankMan.output();
}