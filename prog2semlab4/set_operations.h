#pragma once
#ifndef SET_OPERATIONS_H
#define SET_OPERATIONS_H

#include "list.h"

bool IsSubset(const Form_V& subset, const Form_V& mainSet);
void Intersection(const Form_V& s1, const Form_V& s2, Form_V& result);
bool CheckS3SubsetIntersection(const Form_V& s1, const Form_V& s2, const Form_V& s3);

#endif