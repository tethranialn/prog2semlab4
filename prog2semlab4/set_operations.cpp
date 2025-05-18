#include "set_operations.h"
#include "list.h"
#include "copyS.h"

#define MAX_FULL_STR 1024

static void GetFullString(const EL_V* level, char* buffer, unsigned max) {
    if (!level || max == 0) {
        buffer[0] = '\0';
        return;
    }
    unsigned pos = 0;
    EL_Stroka* current = level->F.h;
    while (current && pos < max - 1) {
        const char* part = current->A;
        unsigned i = 0;
        while (pos < max - 1 && part[i] != '\0') {
            buffer[pos++] = part[i++];
        }
        current = current->next;
    }
    buffer[pos] = '\0';
}

void Intersection(const Form_V& s1, const Form_V& s2, Form_V& result) {
    InitFormV(result);

    EL_V* level1 = s1.h;
    EL_V* level2 = s2.h;

    while (level1 && level2) {
        char str1[MAX_FULL_STR];
        char str2[MAX_FULL_STR];
        GetFullString(level1, str1, MAX_FULL_STR);
        GetFullString(level2, str2, MAX_FULL_STR);

        int cmp = CompareStrings(str1, str2);

        if (cmp == 0) {
            EL_V* newLevel = new EL_V;
            InitELV(newLevel);
            EL_Stroka* current = level1->F.h;
            while (current) {
                InsertString(newLevel->F, current->A);
                current = current->next;
            }
            if (!result.h) {
                result.h = result.last = newLevel;
            }
            else {
                result.last->next = newLevel;
                result.last = newLevel;
            }
            level1 = level1->next;
            level2 = level2->next;
        }
        else if (cmp < 0) {
            level1 = level1->next;
        }
        else {
            level2 = level2->next;
        }
    }
}

bool IsSubset(const Form_V& subset, const Form_V& mainSet) {
    EL_V* subLevel = subset.h;
    EL_V* mainLevel = mainSet.h;

    while (subLevel && mainLevel) {
        char subStr[MAX_FULL_STR];
        char mainStr[MAX_FULL_STR];
        GetFullString(subLevel, subStr, MAX_FULL_STR);
        GetFullString(mainLevel, mainStr, MAX_FULL_STR);

        int cmp = CompareStrings(subStr, mainStr);

        if (cmp == 0) {
            subLevel = subLevel->next;
            mainLevel = mainLevel->next;
        }
        else if (cmp < 0) {
            return false;
        }
        else {
            mainLevel = mainLevel->next;
        }
    }

    return subLevel == nullptr;
}