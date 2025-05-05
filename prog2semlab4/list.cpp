#include "list.h"
#include "copyS.h"
#include <iostream>

void InitELStroka(EL_Stroka*& el, const char* value) {
    el = new EL_Stroka;
    CopyString(el->A, value, N);
    el->next = nullptr;
}

void InitFormStroka(Form_Stroka& fs) {
    fs.h = fs.l = nullptr;
    fs.L = 0;
}

void InitELV(EL_V*& el) {
    el = new EL_V;
    InitFormStroka(el->F);
    el->next = nullptr;
}

void InitFormV(Form_V& fv) {
    fv.h = fv.cur = fv.last = nullptr;
}

void InsertString(Form_Stroka& fs, const char* value) {
    EL_Stroka* newEl;
    InitELStroka(newEl, value);

    if (!fs.h) {
        fs.h = fs.l = newEl;
        fs.L = 1;
        return;
    }

    // Вставка в конец (без сортировки)
    fs.l->next = newEl;
    fs.l = newEl;
    fs.L++;
}

void PrintHierarchy(const Form_V& list, std::ostream& out, const char* name) {
    out << "--- " << name << " ---\n";
    EL_V* level1 = list.h;
    while (level1) {
        EL_Stroka* level2 = level1->F.h;
        bool firstElement = true;
        while (level2) {
            if (!firstElement) out << " -> ";
            out << "[" << level2->A << "]";
            firstElement = false;
            level2 = level2->next;
        }
        level1 = level1->next;
        if (level1) out << "\n\\/";
        out << "\n";
    }
    out << "----------------\n\n";
}