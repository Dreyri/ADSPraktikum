#ifndef MYALGORITHMS_H
#define MYALGORITHMS_H

#include <vector>


namespace ADS
{

using VecRefi = std::vector<int>&;
using VecRefd = std::vector<double>&;

void max_heapify(VecRefi a, int i, int n);
void HeapSort(VecRefi a, int n);

void Merge(VecRefi a, VecRefi b, int low, int pivot, int high);
void MergeSort(VecRefi a, VecRefi b, int low, int high);

void QuickSort(VecRefi arr, int left, int right);

//TODO shellsort

void MatrixMul_ColMajor(VecRefd a, VecRefd b, VecRefd c, int n);

void MatrixMul_RowMajor(VecRefd a, VecRefd b, VecRefd c, int n);
}

#endif // MYALGORITHMS_H
