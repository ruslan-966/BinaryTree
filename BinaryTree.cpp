#include "binarytree.h"
#include <iostream>
BinaryTree::Node::Node(int d, Node* p) :
    data(d), parent(p) {
    leftChild = nullptr;
    rightChild = nullptr;
}
//
BinaryTree::Node::~Node() {
    // чистим за собой память
    if (rightChild != nullptr)
        delete rightChild;
    if (leftChild != nullptr)
        delete leftChild;
}
//
BinaryTree::BinaryTree() {
    root = nullptr;
}
//
BinaryTree::~BinaryTree() {
    if (root != nullptr)
    {
        delete root;
    }
}
void BinaryTree::addInt(int newdata) {
    if (root == nullptr) {
        // если дерево пустое, то новый элемент станет корнем
        root = new Node(newdata);
    }
    else {
        Node* current = root; // начинаем с корня
        Node* newNode = nullptr;
        while (newNode == nullptr) {
            if (current->data >= newdata) {
                // если элемент меньше текущего, идем влево
                if (current->leftChild != nullptr) {
                    current = current->leftChild;
                    continue;
                }
                // если левого узла нет, то нашли место для нового элемента
                newNode = new Node(newdata, current);
                current->leftChild = newNode;
            }
            else {
                // если элемент меньше текущего, идем вправо
                if (current->rightChild != nullptr) {
                    current = current->rightChild;
                    continue;
                }
                // если правого узла нет, то нашли место для нового элемента
                newNode = new Node(newdata, current);
                current->rightChild = newNode;
            }
        }
    }
}
// проверка является ли узел листом        
bool BinaryTree::isLeaf(Node* check) {
    return check->leftChild == nullptr
        && check->rightChild == nullptr;
}

// проверка, являтся ли узел корневым
bool BinaryTree::isRoot(Node* check) {
    return check == root;
}
//---------
// поиск, возвращает указатель на найденный элемент
BinaryTree::Node* BinaryTree::findNodeByData(int finddata) {
    // Ваш код
    Node* queue[100];
    int queuecounter = 1;
    queue[0] = root;

    while (queuecounter != 0)
    {
        // обработка очереди
        Node* current = queue[0];
        queuecounter--;
        for (int i = 0; i < queuecounter; ++i)
            queue[i] = queue[i + 1];
        // сравнение данных
        if (current->data == finddata)
            return current;
        if (current->leftChild)
            queue[queuecounter++] = current->leftChild;
        if (current->rightChild)
            queue[queuecounter++] = current->rightChild;
    }
    return nullptr;
}
// удаление элемента
void BinaryTree::delInt(int deldata) {
    // Ваш код
    // находим указатель на удаляемый узел
    Node* pDel = findNodeByData(deldata);
    Node* pParent = pDel->parent;
    // если это лист, то удаляем (нет обеих ветвей)
    if (isLeaf(pDel))
    {
        if (pParent->leftChild == pDel)
            pParent->leftChild = nullptr;
        else
            pParent->rightChild = nullptr;

        delete pDel;
        return;
    }
    
    if (!pDel->rightChild)    // если нет правой ветви у удаляемой вершины, перезаписываем указатель ребенка в родителя
    {
        if (pParent->leftChild == pDel)
        {
            pParent->leftChild = pDel->leftChild;
            pDel->leftChild->parent = pParent;
        }
            
        else
            pParent->rightChild = pDel->leftChild;
                           
        pDel->leftChild = nullptr;
        pDel->parent = nullptr;
        delete pDel;
        return;
    }
    if (!pDel->leftChild)    // если нет левой ветви у удаляемой вершины, перезаписываем указатель ребенка в родятеля
    {
        if (pParent->leftChild == pDel)
            pParent->leftChild = pDel->rightChild;
        else
        {
            pParent->rightChild = pDel->rightChild;
            pDel->rightChild->parent = pParent;
        }
        
        pDel->rightChild = nullptr;
        pDel->parent = nullptr;
        delete pDel;
        return;
    }
    // существуют обе ветви у удаляемой вершины
    // в левой подветви идем по правым детям и ищем последнего, у которого нет правого ребенка
    Node* current = pDel->leftChild;

    while (current->rightChild)   // в левом поддереве ищем последнюю правую вершину (rightChild = nullptr)
    {
        current = current->rightChild;
    }
    
    // вершину нашли, она может существовать в двух вариантах: либо вершина это лист, либо имеет левого ребенка.
    if (isLeaf(current))
    {
        // вместо того. что бы удалить вершину, записываем в нее данные из вершины current, затем current удаляем за ненадобностью
        pDel->data = current->data;
        current->parent->rightChild = nullptr;
    }
    else
    {
        // перезаписываем данные из найденной вершины в вершину для удаления
        pDel->data = current->data;
        // исключаем вершину current из графа
        current->parent->rightChild = current->leftChild;
        current->leftChild->parent = pDel;
    }
    delete current;
    return;
}

void BinaryTree::print()
{
    if (root == nullptr) return;
    std::cout << "Вершина дерева: " << root->data << std::endl;

    print_obj(root->leftChild);
    print_obj(root->rightChild);
}

void BinaryTree::print_obj(Node* obj)
{
    if (obj == nullptr) return;
    if(obj->parent->data > obj->data)
        std::cout << obj->data << " <- " << obj->parent->data << std::endl;
    else
        std::cout << obj->parent->data << " -> " << obj->data << std::endl;

    print_obj(obj->leftChild);
    print_obj(obj->rightChild);
}

// симметричный обход
void BinaryTree::symmetricWalk(int output_array[]) {
    // положите в output_array[] элементы дерева в порядке их обхода
    // в итоге должен получиться отсортированный массив по возрастанию
    // Ваш код должен быть здесь
    if (root == nullptr) return;
    Node* stack[100];       //создали стек
    for (int i = 0; i < 100; ++i)
        stack[i] = nullptr;
    
    stack[0] = root;
    int stCount = 1;        // счетчик содержимого стека
    int outputCount = 0;    // количество выведенных чисел
    while (stCount != 0)
    {
        Node* current = stack[stCount - 1];
        
        if (!current->leftChild && !current->rightChild)    // это лист, печатаем, удаляем из стека, выходим
        {
            output_array[outputCount++] = current->data;
            stack[--stCount] = nullptr;
            continue;
        }
        else if (current->leftChild && !current->rightChild)      // есть левый ребенок. Два варианта, если ребенок не выведен, его в стек или печть и удаление из стека
        {
            bool isChildWrite = false;
            for (int i = 0; i < outputCount; ++i)
                if (current->leftChild->data == output_array[i])
                {
                    isChildWrite = true;
                    break;
                }
            if (isChildWrite)
            {
                output_array[outputCount++] = current->data;
                stack[--stCount] = nullptr;
                continue;
            }
            else
            {
                stack[stCount++] = current->leftChild;
                continue;
            }
        }
        else if (!current->leftChild && current->rightChild)     // есть правый ребенок. Печать данных узла, замена узла в стеке на ребенка
        {
            output_array[outputCount++] = current->data;
            stack[stCount - 1] = current->rightChild;
        }
        else                // есть два ребенка. если не печатали левого, то его в стек. Если левый напчечатан, то печать узла и замена в стеке на правого ребенка
        {
            bool isChildWrite = false;
            for (int i = 0; i < outputCount; ++i)
                if (current->leftChild->data == output_array[i])
                {
                    isChildWrite = true;
                    break;
                }
            if (!isChildWrite)
            {
                stack[stCount++] = current->leftChild;
                continue;
            }
            else
            {
                output_array[outputCount++] = current->data;
                stack[stCount - 1] = current->rightChild;
                continue;
            }
        }
    }
    for (int i = 0; i < outputCount; ++i)
        std::cout << output_array[i] << " ";
    std::cout << std::endl;
}


