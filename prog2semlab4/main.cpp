#include "list.h"
#include "InpS.h"
#include "DelS.h"
#include "set_operations.h"
#include <iostream>
#include <fstream>

        int main() {
            Form_V S1, S2, S3;
            setlocale(LC_ALL, "Russian");
            InpThreeSets(S1, S2, S3, "input.txt");

            std::ofstream fout("result.txt");
            PrintHierarchy(S1, fout, "S1");
            PrintHierarchy(S2, fout, "S2");
            PrintHierarchy(S3, fout, "S3");

            Form_V intersection;
            Intersection(S1, S2, intersection);
            PrintHierarchy(intersection, fout, "S1 п S2");

            bool isSubset = IsSubset(S3, intersection);
            fout << "Результат:\nS3 с (S1 п S2): " << (isSubset ? "Истина" : "Ложь") << "\n";

            Delete(S1);
            Delete(S2);
            Delete(S3);
            Delete(intersection);
            fout.close();

            return 0;
        }