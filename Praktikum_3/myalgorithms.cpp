#include "myalgorithms.h"

namespace ADS {

void Merge(VecRefi a, VecRefi b, int low, int pivot, int high)
{

}

void MergeSort(VecRefi a, VecRefi b, int low, int high)
{
    //TODO implement
}


void QuickSort(VecRefi a, int left, int right)
{
    int i = left, j = right;
    int tmp;
    int pivot = a[(left + right) / 2];

    /* partition */
    while (i <= j) {
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i <= j) {
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        QuickSort(a, left, j);
    if (i < right)
        QuickSort(a, i, right);
}



void MatrixMul_ColMajor(VecRefd a, VecRefd b, VecRefd c, size_t n)
{
    size_t lda = n;
    size_t ldb = n;
    size_t ldc = n;

    double s = 0.0;

    for(size_t i = 0; i<n; ++i)
    {
        for(size_t j = 0; j<n; ++j)
        {
            s = 0.0;
            for(size_t k = 0; k<n; ++k)
            {
                s = s + a[i+k*lda] * b[k+j*ldb];
            }

            c[i+j*ldc] = s;
        }
    }
}

void MatrixMul_RowMajor(VecRefd a, VecRefd b, VecRefd c, size_t n)
{
    size_t lda = n;
    size_t ldb = n;
    size_t ldc = n;

    double s = 0.0;

    for(size_t i = 0; i<n; ++i)
    {
        for(size_t j = 0; j<n; ++j)
        {
            s = 0.0;
            for(size_t k = 0; k<n; ++k)
            {
                s = s + a[k+j*lda] * b[i+k*ldb];
            }

            c[j+i*ldc] = s;
        }
    }
}

}
