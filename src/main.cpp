#include <iostream>
#include "Reader.h"
#include "Calculation.h"

/*
MAIN
*/

int main()
{
    Reader r1("../test/test4.csv",',');
    vector<vector<float> > matrix = r1.get_matrix();
    bool contain_none = r1.if_contain_none();

    //Calculation cal1(3,matrix);

    for(int i = 0; i < matrix.size();++i)
    { 
        cout<<i<<" "<<matrix[i][0]<<"  "<<matrix[i][1]<<endl;
    }

    return 0;
}
