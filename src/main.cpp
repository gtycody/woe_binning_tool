#include <iostream>
#include "Reader.h"
#include "Calculation.h"

/*
MAIN
*/

int main()
{
    Reader r1("../test/test3.csv");
    vector<vector<float> > matrix = r1.get_matrix();
    Calculation cal1(3,matrix);

    return 0;
}
