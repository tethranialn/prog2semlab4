// main.cpp
#include "list_operations.h"
#include <iostream>

int main() {
    ListCollection collection;
    initializeCollection(collection);

    // Создаем и заполняем списки
    List* list1 = addListToCollection(collection);
    List* list2 = addListToCollection(collection);
    List* list3 = addListToCollection(collection);

    // Чтение данных из файлов
    readFromFile(*list1, "input1.txt");
    readFromFile(*list2, "input2.txt");
    readFromFile(*list3, "input3.txt");

    // Проверка условия S3 ⊂ (S1 ∩ S2)
    bool condition = checkCondition(*list1, *list2, *list3);

    std::cout << "The condition S3 ⊂ (S1 ∩ S2) is "
        << (condition ? "TRUE" : "FALSE") << std::endl;

    // Освобождение памяти
    freeCollection(collection);

    return 0;
}