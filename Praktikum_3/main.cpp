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

int sorting(void)
{
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

    return 0;
}

void transpose3x3(VecRefd mat)
{
    std::swap(mat[1], mat[3]);
    std::swap(mat[2], mat[6]);
    std::swap(mat[5], mat[7]);
}

int matrixMult(void) __attribute__ ((optnone))
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

    //TODO wrong row major multiplication
    MatrixMul_RowMajor(matRA, matRB, resRC, 2);
    std::cout << "******C******" << std::endl;
    std::cout << resRC << std::endl << std::endl;

    std::cout << "Stress test:" << std::endl;
    std::cout << "Col major: " << std::endl;
    std::cout << "generating 1000 3x3 matrices, with field vals: 1-30" << std::endl;

    std::vector<std::vector<double>> ourMatrices(1000);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 30);
    auto dice = [&generator,&distribution]() -> int { return distribution(generator); };

    std::vector<std::vector<double>> resCol(1000, std::vector<double>(9));
    std::vector<std::vector<double>> resRow(1000, std::vector<double>(9));

    for(int i = 0; i < 1000; ++i)
    {
        std::vector<double> mat(9);
        for(int j = 0; j < 9; ++j)
            mat[j] = dice();

        ourMatrices[i] = mat;
    }

    std::cout << "performing 1000 column major multiplications" << std::endl;

    auto start = system_clock::now();

    for(int i = 0; i < 1000; ++i)
    {
        MatrixMul_ColMajor(ourMatrices[i], ourMatrices[999 - i], resCol[i], 3);

    }

    auto end = system_clock::now();

    std::cout << "1000 column major multiplications complete" << std::endl;
    std::cout << "time taken (ms): " << duration_cast<milliseconds>(end - start).count() << std::endl;

    std::cout << "converting to row major" << std::endl;

    for(int i = 0; i < 1000; ++i)
    {
        transpose3x3(ourMatrices[i]);
    }

    std::cout << "performing 1000 row major multiplications" << std::endl;

    start = system_clock::now();

    for(int i = 0; i < 1000; ++i)
    {
        MatrixMul_RowMajor(ourMatrices[i], ourMatrices[999-i], resRow[i], 3);
    }

    end = system_clock::now();

    std::cout << "1000 row major multiplications complete" << std::endl;
    std::cout << "time taken (ms): " << duration_cast<milliseconds>(end - start).count() << std::endl;

    std::cout << "comparing results" << std::endl;

    for(int i = 0; i < 1000; ++i)
    {
        transpose3x3(resRow[i]);

        for(int j = 0; j < 9; ++j)
        {
            if(resCol[i][j] != resRow[i][j])
                std::cout << "Results are not equal! something went wrong!" << std::endl;
        }
    }

    std::cout << "if no complaints all results are equal yay!" << std::endl;






    return 0;
}

int main(void)
{
    return matrixMult();
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
