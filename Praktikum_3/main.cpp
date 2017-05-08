#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <omp.h>
#include "myalgorithms.h"

using namespace std;
using namespace ADS;

ostream& operator<< (ostream& os, std::vector<int>& vec)
{
    for(int i : vec)
    {
        os << i << ", ";
    }

    return os;
}

int main(void)
{
    std::vector<int> myList = { 98, 44, 30, 22, 64, 63, 11, 23, 8, 18 };

    std::cout << "current list: " << myList << std::endl;

    //make sure we reduce size by one or we point too far
    QuickSort(myList, 0, myList.size()-1);

    std::cout << "sorted list: " << myList << std::endl;
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
