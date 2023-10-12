/*

СРР

#include <iostream>
#include <climits>
using namespace std;
 
// Структура данных для хранения узла BST
struct Node
{
    int data;
    Node* left = nullptr, *right = nullptr;
 
    Node() {}
    Node(int data): data(data) {}
};
 
// Рекурсивная функция для вставки ключа в BST
Node* insert(Node* root, int key)
{
    // если корень нулевой, создаем новый узел и возвращаем его
    if (root == nullptr) {
        return new Node(key);
    }
 
    // если заданный ключ меньше корневого узла, повторить для левого поддерева
    if (key < root->data) {
        root->left = insert(root->left, key);
    }
    // если данный ключ больше, чем корневой узел, повторить для правого поддерева
    else {
        root->right = insert(root->right, key);
    }
 
    return root;
}
 
// Функция для определения того, является ли данное бинарное дерево BST, сохраняя
// допустимый диапазон (начиная с [-INFINITY, INFINITY]) и продолжаем уменьшаться
// это вниз для каждого узла, поскольку мы спускаемся рекурсивно
bool isBST(Node* node, int minKey, int maxKey)
{
    // базовый вариант
    if (node == nullptr) {
        return true;
    }
 
    // если значение узла выходит за допустимый диапазон
    if (node->data < minKey || node->data > maxKey) {
        return false;
    }
 
    // рекурсивно проверяем левое и правое поддеревья с обновленным диапазоном
    return isBST(node->left, minKey, node->data) &&
            isBST(node->right, node->data, maxKey);
}
 
// Функция для определения того, является ли данное бинарное дерево BST
void isBST(Node* root)
{
    if (isBST(root, INT_MIN, INT_MAX)) {
        printf("The tree is a BST.");
    }
    else {
        printf("The tree is not a BST!");
    }
}
 
int main()
{
    int keys[] = { 15, 10, 20, 8, 12, 16, 25 };
 
    Node* root = nullptr;
    for (int key: keys) {
        root = insert(root, key);
    }
 
    // поменять местами узлы
    swap(root->left, root->right);
    isBST(root);
 
    return 0;
}*/