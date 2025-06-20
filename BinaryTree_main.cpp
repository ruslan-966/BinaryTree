﻿#include <iostream>
#include "BinaryTree.h"

int main()
{
    setlocale(LC_ALL, "");
    int arr[100];

    BinaryTree btree;

    btree.addInt(5);
    btree.addInt(4);
    btree.addInt(-17);
    btree.addInt(20);
    btree.addInt(43);
    btree.addInt(45);
    btree.addInt(13);
    btree.addInt(11);
    btree.addInt(18);
    btree.addInt(15);
    btree.addInt(19);

    btree.print();

    btree.symmetricWalk(arr);

    btree.print();

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
