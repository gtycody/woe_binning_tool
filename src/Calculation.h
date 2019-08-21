#ifndef CALCULATION_H
#define CALCULATION_H

#include <vector>
#include <string>
#include <math.h>
#include <limits>

using namespace std;

class Calculation
{
    private:
        vector<vector<float> > a;

        vector<float> woe_table;
        vector<float> cuts;
        vector<float> rangeV;

        vector<int> c0wo;
        vector<int> c1wo;
        
        float range;
        float max;

        float max_float;
        float min_float;

        int segments;
   
        int tot1;
        int tot0;


    public:
        //Constructor
        Calculation(int seg, vector<vector<float> > input);

        //Destructor
        //~Calculation();
    
        //get the total count of 0/1
        int totCount0();
        int totCount1();

        //get the range of data
        vector<float> getRange(float count_max, float count_min);

        //cut the range into different segments->return vector is sorted according to its range
        vector<float> cutit(int segments, float range, float min);

        //count the # of 0/1 different segments->return vector is sorted according to its range
        vector<int> getCount0(int segments, vector<float> cuts);
        vector<int> getCount1(int segments, vector<float> cuts);

        //calculate woe
        vector<float> calWoe(vector<int> c0wo, vector<int> c1wo, int tot1, int tot0);


        //Printing function 
        void print_me(vector<float> woe_table, vector<float> cuts, float max);
        void printAll();

        //change the value in a
        void swap_value(vector<float> woe_table, vector<float> cuts, float max);

};
#endif
