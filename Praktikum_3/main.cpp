#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <omp.h>
#include <chrono>
#include <random>
#include "myalgorithms.h"

using namespace std;
using namespace std::chrono;
using namespace ADS;

void testSort(const std::string& fileName, std::function<void(std::vector<int>& vec)> sortAlgo)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    auto dice = [&generator,&distribution]() -> int { return distribution(generator); };

    std::cout << fileName << std::endl;
    auto rdBuf = std::cout.rdbuf();
    std::cout.rdbuf(nullptr);

    auto startHeapSort = std::chrono::high_resolution_clock::now();

    ofstream file;
    file.open(fileName);

    for(int i = 1000; i <= 1000000; i+=1000)
    {
        std::vector<int> diceVec(i);

        for(int j = 0; j < i; ++j)
        {
            diceVec[j] = dice();
        }

        auto start = std::chrono::high_resolution_clock::now();
        sortAlgo(diceVec);
        auto end = std::chrono::high_resolution_clock::now();

        auto timeMs = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

        std::cout.rdbuf(rdBuf);
        std::cout << "n: " << i << " " << timeMs << std::endl;;
        std::cout.rdbuf(nullptr);

        file << i << "\t" << timeMs << std::endl;

        if(std::chrono::duration_cast<std::chrono::milliseconds>(end-startHeapSort).count() > 600000) //bigger than 10mins, let's stop
            break;
    }

    file.close();
    std::cout.rdbuf(rdBuf);
}

void testMatrixMult(const std::string& fileName, std::function<void(std::vector<double>& a, std::vector<double>& b, std::vector<double>& c, size_t n)> func)
{
    //testing matrixes
    std::default_random_engine generator;
    std::uniform_int_distribution<double> distribution(-1000000.0, 1000000.0); //not too big numbers (overflows etc)
    auto dice = [&generator,&distribution]() -> double { return distribution(generator); };

    ofstream file;
    file.open(fileName);

    auto startTimer = std::chrono::high_resolution_clock::now();

    for(size_t n = 2; n < 799; ++n)
    {
        std::vector<double> randMatrix(n*n);
        std::vector<double> randMatrix1(n*n);
        std::vector<double> resMatrix(n*n);

        //generate matrix
        for(size_t i = 0; i < n*n; ++i)
        {
            randMatrix[i] = dice();
            randMatrix1[i] = dice();
        }

        auto start = std::chrono::high_resolution_clock::now();
        func(randMatrix, randMatrix1, resMatrix, n);
        auto end = std::chrono::high_resolution_clock::now();

        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

        file << n << "\t" << microseconds << std::endl;
        std::cout << "n: " << n << "\t" << microseconds << " microseconds" << std::endl;

        if(std::chrono::duration_cast<std::chrono::seconds>(end-startTimer).count() > 600)
        {
            file.close();
            return;
        }
    }

    for(size_t n = 800; n < 2000; n+=11)
    {
        std::vector<double> randMatrix(n*n);
        std::vector<double> randMatrix1(n*n);
        std::vector<double> resMatrix(n*n);

        //generate matrix
        for(size_t i = 0; i < n*n; ++i)
        {
            randMatrix[i] = dice();
            randMatrix1[i] = dice();
        }

        auto start = std::chrono::high_resolution_clock::now();
        func(randMatrix, randMatrix1, resMatrix, n);
        auto end = std::chrono::high_resolution_clock::now();

        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

        file << n << "\t" << microseconds << std::endl;
        std::cout << "n: " << n << "\t" << microseconds << " microseconds" << std::endl;

        if(std::chrono::duration_cast<std::chrono::seconds>(end-startTimer).count() > 600)
            break;
    }

    file.close();
}

void matrixMultTest()
{

    std::cout << "Mult col major" << std::endl;
    testMatrixMult("col.txt", MatrixMul_ColMajor);

    std::cout << "Mult row major" << std::endl;
    testMatrixMult("row.txt", MatrixMul_RowMajor);

    std::cout << "Mult col major OMP" << std::endl;
    testMatrixMult("colomp.txt", OMP_MatrixMul_ColMajor);

    std::cout << "Mult row major OMP" << std::endl;
    testMatrixMult("rowomp.txt", OMP_MatrixMul_RowMajor);
}

int sorting(void)
{
    std::cout << "Testing algorithm validity:" << std::endl;
    std::vector<int> myList = { 98, 44, 30, 22, 64, 63, 11, 23, 8, 18 };

    std::cout << "current list: " << myList << std::endl;

    //make sure we reduce size by one or we point too far
    //HeapSort(myList, myList.size());
    QuickSort(myList, 0, myList.size()-1);

    std::cout << "quicksorted list: " << myList << std::endl;

    std::vector<int> myList2 = { 98, 44, 30, 22, 64, 63, 11, 23, 8, 18 };

    HeapSort(myList2, myList2.size());

    std::cout << "heapsorted list: " << myList2 << std::endl;

    std::vector<int> myList3 = { 98, 44, 30, 22 ,64, 63, 11, 23, 8, 18 };

    MergeSort(myList3, 0, myList3.size()-1);

    std::cout << "mergesorted list: " << myList3 << std::endl;

    std::vector<int> myList4 = {98, 44, 30, 22, 64, 63, 11, 23, 8, 18 };
    HibbardSort(myList4, myList4.size());
    std::cout << "hibbardsorted list: " << myList4 << std::endl;


    /*
    std::cout << "PERFORMANCE TEST SORTING ALGORITHMS" << std::endl;

    testSort("heapsort.txt", [](std::vector<int>& a)
    {
        HeapSort(a, a.size());
    });

    testSort("quicksort.txt", [](std::vector<int>& a)
    {
        QuickSort(a, 0, a.size()-1);
    });

    testSort("mergesort.txt", [](std::vector<int>& a)
    {
        MergeSort(a, 0, a.size()-1);
    });

    testSort("shellsort.txt", [](std::vector<int>& a)
    {
        HibbardSort(a, a.size());
    });
    */

    matrixMultTest();

    return 0;
}

void transpose3x3(VecRefd mat)
{
    std::swap(mat[1], mat[3]);
    std::swap(mat[2], mat[6]);
    std::swap(mat[5], mat[7]);
}

int matrixMult(void)
{
    {
        std::cout << "spaltenweise: " << std::endl;
        std::vector<double> matA { 1,3,2,4 };
        std::vector<double> matB { 5,7,6,8 };
        std::vector<double> resC(4);

        std::cout << "******A******" << std::endl;
        std::cout << matA << std::endl << std::endl;

        std::cout << "******B******" << std::endl;
        std::cout << matB << std::endl << std::endl;

        MatrixMul_ColMajor(matA, matB, resC, 2);
        std::cout << "******C******" << std::endl;
        std::cout << resC << std::endl << std::endl;

        std::cout << "zeilenweise: " << std::endl;
        std::vector<double> matRA { 1,2,3,4 };
        std::vector<double> matRB { 5,6,7,8 };
        std::vector<double> resRC(4);

        std::cout << "******A******" << std::endl;
        std::cout << matRA << std::endl << std::endl;

        std::cout << "******B******" << std::endl;
        std::cout << matRB << std::endl << std::endl;

        MatrixMul_RowMajor(matRA, matRB, resRC, 2);
        std::cout << "******C******" << std::endl;
        std::cout << resRC << std::endl << std::endl;
    }
    std::cout << std::endl << std::endl << "OMP" << std::endl << std::endl;

    {
        std::cout << "spaltenweise: " << std::endl;
        std::vector<double> matA { 1,3,2,4 };
        std::vector<double> matB { 5,7,6,8 };
        std::vector<double> resC(4);

        std::cout << "******A******" << std::endl;
        std::cout << matA << std::endl << std::endl;

        std::cout << "******B******" << std::endl;
        std::cout << matB << std::endl << std::endl;

        MatrixMul_ColMajor(matA, matB, resC, 2);
        std::cout << "******C******" << std::endl;
        std::cout << resC << std::endl << std::endl;

        std::cout << "zeilenweise: " << std::endl;
        std::vector<double> matRA { 1,2,3,4 };
        std::vector<double> matRB { 5,6,7,8 };
        std::vector<double> resRC(4);

        std::cout << "******A******" << std::endl;
        std::cout << matRA << std::endl << std::endl;

        std::cout << "******B******" << std::endl;
        std::cout << matRB << std::endl << std::endl;

        MatrixMul_RowMajor(matRA, matRB, resRC, 2);
        std::cout << "******C******" << std::endl;
        std::cout << resRC << std::endl << std::endl;
    }

    return 0;
}

int main(void)
{
    matrixMult();
    return sorting();
}


/*
int main(void) {
    ofstream file ;
    file.open("example.txt");
    double dtime;
    int n_start = 1000;
    int n_step = 1000;
    int n_end = 1000000;
    for (int n = n_start; n<n_end; n+=n_step)
    {
        cout << "n: " << n << endl;
        //∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗/
        // init data here //
        //∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗/
        dtime = omp_get_wtime();
        //∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗/
        // run algorithm here //
        //∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗/
        dtime = omp_get_wtime() - dtime;
        file << n << "\t" << scientific << setprecision(10) << dtime << endl;
    }
    file.close();
}
*/
