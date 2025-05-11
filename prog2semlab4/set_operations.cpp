#include "set_operations.h"
#include "list.h"
#include "copyS.h"

// Вспомогательная функция для получения следующего элемента из списка
static const char* GetNextElement(EL_V*& currentLevel, EL_Stroka*& currentElem) {
    while (currentLevel) {
        if (currentElem) {
            const char* value = currentElem->A;
            currentElem = currentElem->next;
            return value;
        }
        currentLevel = currentLevel->next;
        if (currentLevel) currentElem = currentLevel->F.h;
    }
    return nullptr;
}

void Intersection(const Form_V& s1, const Form_V& s2, Form_V& result) {
    InitFormV(result);

    EL_V* level1 = s1.h;
    EL_Stroka* elem1 = level1 ? level1->F.h : nullptr;
    const char* current1 = GetNextElement(level1, elem1);

    EL_V* level2 = s2.h;
    EL_Stroka* elem2 = level2 ? level2->F.h : nullptr;
    const char* current2 = GetNextElement(level2, elem2);

    EL_V* resLevel = nullptr;
    while (current1 && current2) {
        int cmp = CompareStrings(current1, current2);

        if (cmp == 0) {
            if (!resLevel || resLevel->F.L >= 3) {
                EL_V* newLevel = new EL_V;
                InitELV(newLevel);
                if (!result.h) result.h = result.last = newLevel;
                else result.last->next = newLevel;
                result.last = newLevel;
                resLevel = newLevel;
            }
            InsertString(resLevel->F, current1);

            current1 = GetNextElement(level1, elem1);
            current2 = GetNextElement(level2, elem2);
        }
        else if (cmp < 0) {
            current1 = GetNextElement(level1, elem1);
        }
        else {
            current2 = GetNextElement(level2, elem2);
        }
    }
}

bool IsSubset(const Form_V& subset, const Form_V& mainSet) {
    EL_V* subLevel = subset.h;
    EL_Stroka* subElem = subLevel ? subLevel->F.h : nullptr;
    const char* currentSub = GetNextElement(subLevel, subElem);

    EL_V* mainLevel = mainSet.h;
    EL_Stroka* mainElem = mainLevel ? mainLevel->F.h : nullptr;
    const char* currentMain = GetNextElement(mainLevel, mainElem);

    while (currentSub && currentMain) {
        int cmp = CompareStrings(currentSub, currentMain);

        if (cmp == 0) {
            currentSub = GetNextElement(subLevel, subElem);
            currentMain = GetNextElement(mainLevel, mainElem);
        }
        else if (cmp < 0) {
            return false;
        }
        else {
            currentMain = GetNextElement(mainLevel, mainElem);
        }
    }
    return !currentSub;
}