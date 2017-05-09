#ifndef MYALGORITHMS_H
#define MYALGORITHMS_H

#include <vector>
#include <iostream>


namespace ADS
{

using VecRefi = std::vector<int>&;
using VecRefd = std::vector<double>&;

template<typename T>
std::ostream& operator<< (std::ostream& os, std::vector<T>& vec);

void max_heapify(VecRefi a, int i, int n);
void HeapSort(VecRefi a, int n);

void Merge(VecRefi a, int low, int pivot, int high);
void MergeSort(VecRefi a, int low, int high);

void QuickSort(VecRefi arr, int left, int right);
void HibbardSort(VecRefi a, int n);

void MatrixMul_ColMajor(VecRefd a, VecRefd b, VecRefd c, size_t n);
void MatrixMul_RowMajor(VecRefd a, VecRefd b, VecRefd c, size_t n);

void OMP_MatrixMul_ColMajor(VecRefd a, VecRefd b, VecRefd c, size_t n);
void OMP_MatrixMul_RowMajor(VecRefd a, VecRefd b, VecRefd c, size_t n);
}

#endif // MYALGORITHMS_H
