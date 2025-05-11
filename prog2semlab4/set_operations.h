#pragma once
#ifndef SET_OPERATIONS_H
#define SET_OPERATIONS_H

#include "list.h"

// Проверяет, является ли subset подмножеством mainSet
bool IsSubset(const Form_V& subset, const Form_V& mainSet);

// Вычисляет пересечение множеств s1 и s2, результат в result
void Intersection(const Form_V& s1, const Form_V& s2, Form_V& result);

#endif