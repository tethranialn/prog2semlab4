#include "set_operations.h"
#include "list.h"
#include "copyS.h"
#include <vector>
#include <algorithm>

// Вспомогательная функция: собирает все элементы списка в плоский вектор
static void FlattenList(const Form_V& list, std::vector<const char*>& result) {
    EL_V* level = list.h;
    while (level) {
        EL_Stroka* elem = level->F.h;
        while (elem) {
            result.push_back(elem->A);
            elem = elem->next;
        }
        level = level->next;
    }
}

// Реализация пересечения множеств
void Intersection(const Form_V& s1, const Form_V& s2, Form_V& result) {
    InitFormV(result);

    std::vector<const char*> elementsS1;
    std::vector<const char*> elementsS2;
    FlattenList(s1, elementsS1);
    FlattenList(s2, elementsS2);

    // Сортировка элементов
    std::sort(elementsS1.begin(), elementsS1.end(), [](const char* a, const char* b) {
        return CompareStrings(a, b) < 0;
        });
    std::sort(elementsS2.begin(), elementsS2.end(), [](const char* a, const char* b) {
        return CompareStrings(a, b) < 0;
        });

    // Поиск пересечения
    std::vector<const char*> intersection;
    std::set_intersection(
        elementsS1.begin(), elementsS1.end(),
        elementsS2.begin(), elementsS2.end(),
        std::back_inserter(intersection),
        [](const char* a, const char* b) {
            return CompareStrings(a, b) < 0;
        }
    );

    // Формирование результата с сохранением порядка
    EL_V* currentLevel = nullptr;
    for (const char* elem : intersection) {
        if (!currentLevel || currentLevel->F.L >= 3) {
            EL_V* newLevel = new EL_V;
            InitELV(newLevel);
            if (!result.h) result.h = result.last = newLevel;
            else result.last->next = newLevel;
            result.last = newLevel;
            currentLevel = newLevel;
        }
        InsertString(currentLevel->F, elem);
    }
}
// Проверка подмножества
bool IsSubset(const Form_V& subset, const Form_V& mainSet) {
    std::vector<const char*> elementsSubset;
    std::vector<const char*> elementsMain;
    FlattenList(subset, elementsSubset);
    FlattenList(mainSet, elementsMain);

    // Сортировка
    std::sort(elementsSubset.begin(), elementsSubset.end(), [](const char* a, const char* b) {
        return CompareStrings(a, b) < 0;
        });
    std::sort(elementsMain.begin(), elementsMain.end(), [](const char* a, const char* b) {
        return CompareStrings(a, b) < 0;
        });

    // Проверка подмножества
    auto itSub = elementsSubset.begin();
    auto itMain = elementsMain.begin();

    while (itSub != elementsSubset.end() && itMain != elementsMain.end()) {
        int cmp = CompareStrings(*itSub, *itMain);
        if (cmp == 0) {
            ++itSub;
            ++itMain;
        }
        else if (cmp < 0) {
            return false;
        }
        else {
            ++itMain;
        }
    }

    return (itSub == elementsSubset.end());
}