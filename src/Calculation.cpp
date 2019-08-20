#include <iostream>
#include "Calculation.h"

//#include <vector> //required
//#include <limits> //since MAX and MIN num are recorded in limits
//#include <math.h> //input natural log

//Constructor
Calculation::Calculation(int seg)
{
    segments = seg;  //set how many segments it need
    cout<<"cut into: "<<segments<<"\n";

    // finding the range of existing datai
    max_float = numeric_limits<float>::min();
    min_float = numeric_limits<float>::max();
   
    tot1 = totCount1();
    tot0 = totCount0();

    rangeV = getRange(max_float, min_float);
    range = rangeV[0]-rangeV[1];
    cuts = cutit(segments, range, rangeV[1]);

    c0wo = getCount0(segments,cuts);
    c1wo = getCount1(segments,cuts);
    woe_table = calWoe(c0wo,c1wo,tot1,tot0);

    
    swap_value(woe_table, cuts, rangeV[0]);

    //printAll();

    print_me(woe_table, cuts, rangeV[0]);
}


//get 0 count
vector<int> Calculation::getCount0(int segments, vector<float> cuts)
{
    vector<int> count0wo; 
    cuts.push_back(numeric_limits<int>::max());    

    for(int i = 0; i < segments; ++i)
    {  
        count0wo.push_back(0);
    }
    for(int j = 0; j< a.size()-1; ++j)
    {
        for(int k = 0; k < segments; ++k)
        {
            if( (a[j][0] >= cuts[k]) && (a[j][0] <= cuts[k+1]) && (a[j][1] == 0) )
            {   
                ++count0wo[k]; 
                break;
            }
        }
    }
    return count0wo;
}


//get 1 count
vector<int> Calculation::getCount1(int segments, vector<float> cuts)
{
    vector<int> count1wo; 
    cuts.push_back(numeric_limits<int>::max());    
    
    for(int i = 0; i < segments; ++i)
    {  
        count1wo.push_back(0);
    }
    for(int j = 0; j< a.size()-1; ++j)
    {
        for(int k = 0; k < segments; ++k)
        {
            if( (a[j][0] >= cuts[k]) && (a[j][0] <= cuts[k+1]) && (a[j][1]==1))
            {   
                ++count1wo[k]; 
                break;
            }
        }
    }
    return count1wo;
}


//cut range
vector<float> Calculation::cutit(int segments, float range, float min)
{
    vector<float> cuts;
    for(int i = 0; i < segments; ++i)
    {
        cuts.push_back(min + range / segments * i);
    }
    return cuts;
}


//Count total # of 0
int Calculation::totCount0()
{
    int count = 0;
    for(int i = 0;i < a.size()-1;i++)
    {
        if(a[i][1] == 0)
        {
            ++ count;
        }
    }
    return count;
}


//Count total # of 1
int Calculation::totCount1()
{
    int count = 0;
    for(int i = 0;i < a.size()-1; ++i)
    {
        if(a[i][1] == 1)
        {
            ++ count;
        }  
    }
    return count;
}


//get range
vector<float> Calculation::getRange(float max_float, float min_float)
{
    for(int i = 0; i < a.size()-1; i++)
    {
        if(max_float < a[i][0])
        {
            max_float = a[i][0];
        }
        if(min_float > a[i][0])
        {
            min_float = a[i][0];
        }
    }
    vector<float> vec;
    vec.push_back(max_float);
    vec.push_back(min_float);
    return vec;  
}


//calcuate woe value and return by vector
vector<float> Calculation::calWoe(vector<int> c0wo, vector<int> c1wo, int tot1, int tot0)
{
    vector<float> woe_table;
    for(int i = 0; i < c0wo.size(); ++i)
    {
        float woe = log( ((float)c1wo[i]/tot1) / ((float)c0wo[i]/tot0) );
        woe_table.push_back(woe);
    }
    return woe_table;
}


//replace the woe value
void Calculation::swap_value(vector<float> woe_table, vector<float> cuts, float max)
{
    cuts.push_back(max);
    for (int i = 0; i < a.size()-1; ++i)
    {
        for(int j = 0; j < woe_table.size(); ++j)
        {
            if ((cuts[j]<=a[i][0]) && (a[i][0]<=cuts[j+1]))
            {
                a[i][0] = woe_table[j];
                break;
            }          
        }
    }
}


//printing the columns
void Calculation::printAll()
{
    for(int i = 0; i < a.size()-1; ++i)
    {
        cout<<i<<"   "<<a[i][0]<<"   "<<a[i][1]<<endl;
    }
}


//printing out function
void Calculation::print_me(vector<float> woe_table, vector<float> cuts, float max)
{
    cuts.push_back(max);
    for (int i = 0; i < woe_table.size(); ++i)
    {
        cout<<cuts[i]<<"-"<<cuts[i+1]<<":       "<<woe_table[i]<<endl;
    }
}

