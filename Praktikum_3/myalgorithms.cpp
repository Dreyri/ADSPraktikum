#include "myalgorithms.h"

#include <cmath>

namespace ADS {

template<>
std::ostream& operator<< (std::ostream& os, std::vector<int>& vec)
{
    for(int i : vec)
    {
        os << i << ", ";
    }

    return os;
}

template<>
std::ostream& operator<< (std::ostream& os, std::vector<double>& vec)
{
    for(int i : vec)
    {
        os << i << ", ";
    }

    return os;
}

void max_heapify(VecRefi a, int i, int n)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    std::cout << "heapify(a, " << i << ", " << n << ")" << std::endl;

    //if left child is larger than root
    if(l < n && a[l] > a[largest])
    {
        largest = l;
    }
    //if right child is larger than largest so far
    if(r < n && a[r] > a[largest])
    {
        largest = r;
    }
    //if largest is not root
    if(largest != i)
    {
        std::swap(a[i], a[largest]);

        //heapify the sub-tree
        max_heapify(a, largest, n);
    }
}

void HeapSort(VecRefi a, int n)
{
    //build heap
    for(int i = n / 2 - 1; i >= 0; --i)
    {
        max_heapify(a, i, n);
    }

    std::cout << "Max heap aufgebaut:" << std::endl;
    std::cout << a << std::endl;

    //extract heap elements one by one
    for(int i = n-1; i >= 0; --i)
    {
        std::swap(a[0], a[i]);

        //heapify the reduced heap
        max_heapify(a, 0, i);

        std::cout << "Durchlauf: " << i << ": " << a << std::endl;
    }
}

void Merge(VecRefi a, int low, int pivot, int high)
{
    std::cout << "Merge(a, " << "low: " << low << ", pivot: " << pivot << ", high: " << high << ")" << std::endl;

    int i, j, k;
        int n1 = pivot - low + 1;
        int n2 =  high - pivot;

        /* create temp arrays */
        int L[n1], R[n2];

        /* Copy data to temp arrays L[] and R[] */
        for (i = 0; i < n1; i++)
            L[i] = a[low + i];
        for (j = 0; j < n2; j++)
            R[j] = a[pivot + 1+ j];

        /* Merge the temp arrays back into arr[l..r]*/
        i = 0; // Initial index of first subarray
        j = 0; // Initial index of second subarray
        k = low; // Initial index of merged subarray
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                a[k] = L[i];
                i++;
            }
            else
            {
                a[k] = R[j];
                j++;
            }
            k++;
        }

        /* Copy the remaining elements of L[], if there
           are any */
        while (i < n1)
        {
            a[k] = L[i];
            i++;
            k++;
        }

        /* Copy the remaining elements of R[], if there
           are any */
        while (j < n2)
        {
            a[k] = R[j];
            j++;
            k++;
        }
}

void MergeSort(VecRefi a, int low, int high)
{
    std::cout << "MergeSort(a, low: " << low << ", high: " << high << ")" << std::endl;
    if (low < high)
        {
            // Same as (low+high)/2, but avoids overflow for
            // large low and high
            auto m = low+(high-low)/2;

            // Sort first and second halves
            MergeSort(a, low, m);
            MergeSort(a, m+1, high);

            std::cout << "List before merge " << a << std::endl;

            Merge(a, low, m, high);

            std::cout << "List after merge " << a << std::endl;
        }
}


void QuickSort(VecRefi a, int left, int right)
{
    std::cout << "QuickSort(a, " << left << ", " << right << ")" << std::endl;
    int i = left, j = right;
    int tmp;
    int pivotIndex = (left+right) / 2;
    int pivot = a[pivotIndex];

    std::cout << "Pivot: a["  << pivotIndex << "] = " << pivot << std::endl;

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

    std::cout << "Result : " << a << std::endl;;

    /* recursion */
    if (left < j)
        QuickSort(a, left, j);
    if (i < right)
        QuickSort(a, i, right);
}

void HibbardSort(VecRefi a, int n)
{
    int i,j,k,incr,tmp;

    incr = 1;
    k = 0;

    while(incr <= n+1)
    {
        std::cout << "Hibbard increment: " << incr << std::endl;

        for(i = incr; i <= n-1; ++i)
        {
            tmp = a[i];
            j = i;
            while(j >= incr && a[j-incr] > tmp)
            {
                a[j] = a[j-incr];
                j -= incr;
            }
            a[j] = tmp;
        }
        ++k;
        incr = static_cast<int>(std::pow(2, k))-static_cast<int>(1);
    }
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

void OMP_MatrixMul_ColMajor(VecRefd a, VecRefd b, VecRefd c, size_t n)
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
                s += a[k+i*lda] * b[j+k*ldb];
            }

            c[j+i*ldc] = s;
        }
    }
}

void OMP_MatrixMul_RowMajor(VecRefd a, VecRefd b, VecRefd c, size_t n)
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
                s += a[k+i*lda] * b[j+k*ldb];
            }

            c[j+i*ldc] = s;
        }
    }
}

}
