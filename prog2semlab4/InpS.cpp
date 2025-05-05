#include "InpS.h"
#include "list.h"
#include "copyS.h"
#include <fstream>
#include <algorithm>

void InpThreeSets(Form_V& S1, Form_V& S2, Form_V& S3, const char* filename) {
    InitFormV(S1);
    InitFormV(S2);
    InitFormV(S3);
    std::ifstream fin(filename);
    if (!fin.is_open()) return;

    const int MAX_SETS = 3;
    Form_V* sets[MAX_SETS] = { &S1, &S2, &S3 };
    int currentSet = 0;

    char temp[N];
    EL_V* curV = nullptr;
    int pos = 0;
    char ch;

    while (fin.get(ch)) {
        if (ch == '\n') {
            if (pos > 0) {
                temp[pos] = '\0';
                if (curV) InsertString(curV->F, temp);
                pos = 0;
            }

            if (fin.peek() == '\n') {
                fin.get();
                currentSet = std::min(currentSet + 1, MAX_SETS - 1);
                curV = nullptr;
            }
            else {
                // Создаем новый вертикальный элемент для новой строки
                curV = nullptr;
            }
            continue;
        }

        if (!curV) {
            curV = new EL_V;
            InitELV(curV);
            if (!sets[currentSet]->h) {
                sets[currentSet]->h = sets[currentSet]->last = curV;
            }
            else {
                sets[currentSet]->last->next = curV;
                sets[currentSet]->last = curV;
            }
        }

        temp[pos++] = ch;
        if (pos >= N - 1) {
            temp[pos] = '\0';
            InsertString(curV->F, temp);
            pos = 0;
        }
    }

    if (pos > 0 && curV) {
        temp[pos] = '\0';
        InsertString(curV->F, temp);
    }

    fin.close();
}