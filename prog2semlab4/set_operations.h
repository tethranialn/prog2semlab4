#pragma once
#ifndef SET_OPERATIONS_H
#define SET_OPERATIONS_H

#include "list.h"

// ���������, �������� �� subset ������������� mainSet
bool IsSubset(const Form_V& subset, const Form_V& mainSet);

// ��������� ����������� �������� s1 � s2, ��������� � result
void Intersection(const Form_V& s1, const Form_V& s2, Form_V& result);

#endif