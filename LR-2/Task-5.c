/*


С помощью очереди можно легко найти кратчайший путь коня на шахматной доске. 
Для этого нужно хранить в очереди текущую позицию коня, а также возможные позиции,
в которые он может пойти из текущей. Когда мы достаем позицию из очереди, мы проверяем, 
является ли она заданной конечной позицией, если нет, то добавляем возможные позиции в конец очереди.

Он принимает размер доски (NxN) и начальную и конечную позиции коня в виде кортежей (x1, y1) и (x2, y2) соответственно.

#include <iostream>
#include <set>
#include <queue>
#include <climits>
using namespace std;
 
// Ниже массивы детализируют все восемь возможных движений
// для рыцаря
int row[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int col[] = { -1, 1, 1, -1, 2, -2, 2, -2 };
 
// Проверяем, являются ли (x, y) действительными координатами шахматной доски.
// Обратите внимание, что конь не может выйти за пределы доски
bool isValid(int x, int y, int N) {
    return (x >= 0 && x < N) && (y >= 0 && y < N);
}
 
// Узел queue, используемый в BFS
struct Node
{
    // (x, y) представляет координаты шахматной доски
    // `dist` представляет минимальное расстояние от источника
    int x, y, dist;
 
    // Конструктор узла
    Node(int x, int y, int dist = 0): x(x), y(y), dist(dist) {}
 
    // Поскольку мы используем структуру в качестве ключа в `std::set`,
    // нам нужно перегрузить оператор `<`.
    // В качестве альтернативы мы можем использовать `std::pair<int, int>` в качестве ключа
    // для хранения координат матрицы в наборе.
 
    bool operator<(const Node& o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
};
 
// Находим минимальное количество шагов, которое сделал конь
// из источника в пункт назначения с помощью BFS
int findShortestDistance(int N, Node src, Node dest)
{
    // ставим проверять, была ли ячейка матрицы посещена раньше или нет
    set<Node> visited;
 
    // создаем queue и ставим в queue первый узел
    queue<Node> q;
    q.push(src);
 
    // цикл до тех пор, пока queue не станет пустой
    while (!q.empty())
    {
        // удалить передний узел из очереди и обработать его
        Node node = q.front();
        q.pop();
 
        int x = node.x;
        int y = node.y;
        int dist = node.dist;
 
        // если пункт назначения достигнут, возвращаем расстояние
        if (x == dest.x && y == dest.y) {
            return dist;
        }
 
        // пропустить, если место было посещено раньше
        if (!visited.count(node))
        {
            // отметить текущий узел как посещенный
            visited.insert(node);
 
            // проверка всех восьми возможных движений коня
            // и ставим в queue каждое допустимое движение
            for (int i = 0; i < 8; i++)
            {
                // получаем действительную позицию коня из текущей позиции на
                // шахматная доска и поставить ее в queue с расстоянием +1
                int x1 = x + row[i];
                int y1 = y + col[i];
 
                if (isValid(x1, y1, N)) {
                    q.push({x1, y1, dist + 1});
                }
            }
        }
    }
 
    // возвращаем бесконечность, если путь невозможен
    return INT_MAX;
}
 
int main()
{
    // Матрица N x N
    int N = 8;
 
    // исходные координаты
    Node src = {0, 7};
 
    // координаты пункта назначения
    Node dest = {7, 0};
 
    cout << "The minimum number of steps required is " <<
            findShortestDistance(N, src, dest);
 
    return 0;
}


*/