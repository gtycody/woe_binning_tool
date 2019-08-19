#include <iostream> //emmmmmmmmmmm.........
#include <fstream> //i/o file
#include <string> //required
#include <vector> //required
#include <algorithm> //Maybe useless
#include <typeinfo> //Maybe useless
#include <limits> //since MAX and MIN num are recorded in limits
#include <math.h> //input natural log


//====================================================
//Since I do not use C++ for a long time
//I Shall not able to finish the job to 
//do the whole woe_binnning tool
//but I'll fo it for all 
//filled-in columns with all float  
//====================================================

using namespace std;
 
vector<vector<float> >a;  //read in 2-D list
vector<float> b; //use in reading 2-D list
 
//CSV reading functions
inline void file_to_string(vector<string> &record, const string& line, char delimiter);
inline float string_to_float(string str);

//get the total count of 0/1
int totCount0();
int totCount1();

//get the range of data
inline vector<float> getRange(float count_max, float count_min);

//cut the range into different segments->return vector is sorted according to its range
vector<float> cutit(int segments);

//count the # of 0/1 different segments->return vector is sorted according to its range
vector<int> getCount0(vector<float> cuts);
vector<int> getCount1(vector<float> cuts);

//Printing function 
void print_me(vector<float> woe_table, vector<float> cuts, float max);

//change the value in a
void swap_value(vector<float> woe_table, vector<float> cuts, float max)


//=================================================
//              function initialize
//                 2019 - 8 - 19 
//=================================================

//The O complexity of this function is O(4n) //if default segments
//value is 4
//feel free to optimize if u can get it to O(n)
vector<int> getCount0(int segments, vector<float> cuts){
    vector<int> count0wo; //count0wo : count 0 with order allign with the order of cuts
    cuts.push_back(numeric_limits<int>::max());    
    for(int i = 0; i < segments; ++i){  
        count0wo.push_back(0);
    }
    for(int j = 0; j< a.size()-1; ++j){
        for(int k = 0; k < segments; ++k){
            if( (a[j][0] >= cuts[k]) && (a[j][0] <= cuts[k+1]) && (a[j][1] == 0) ){   
                ++count0wo[k]; 
                break;
            }
        }
    }
    for(int q = 0; q < segments; ++q){
        //cout<<count0wo[q]<<"\n";
    }
    return count0wo;
}


//The O complexity of this function is O(4n) //if default segments
//value is 4
//feel free to optimize if u can get it to O(n)
vector<int> getCount1(int segments, vector<float> cuts){
    vector<int> count1wo; //count0wo : count 0 with order allign with the order of cuts
    cuts.push_back(numeric_limits<int>::max());    
    for(int i = 0; i < segments; ++i){  
        count1wo.push_back(0);
    }
    for(int j = 0; j< a.size()-1; ++j){
        for(int k = 0; k < segments; ++k){
            if( (a[j][0] >= cuts[k]) && (a[j][0] <= cuts[k+1]) && (a[j][1]==1)){   
                ++count1wo[k]; 
                break;
            }
        }
    }
    printf("\n");
    for(int q = 0; q < segments; ++q){
        //cout<<count1wo[q]<<"\n";
    }
    return count1wo;
}


//This function illustrate the way of cutting
//please modify u self if u wanna other cutting stratagies=============================================
vector<float> cutit(int segments, float range, float min){
    vector<float> cuts;
    for(int i = 0; i < segments; ++i){
        cuts.push_back(min + range / segments * i);
        //cout<<cuts[i]<<"\n";
    }
    cout<<"\n";
    return cuts;
}
 

//CSV reading function================================================================================ 
//if u have better idea plz optimize it
void read(string filename){
    vector<string> row;
    string line;

    ifstream in(filename); 

    if (in.fail()){ 
        cout << "File not found" <<endl; 
        return ; 
    } 
   
    while(getline(in, line)  && in.good() ){
        file_to_string(row, line, ','); 
        for(int i=0, leng=row.size(); i<leng; i++){
            b.push_back(string_to_float(row[i]));
        }
        a.push_back(b);
        b.clear();
    }
    in.close();
}

//CSVreader function==================================================================================
inline void file_to_string(vector<string> &record, const string& line, char delimiter)
{
    int linepos = 0;
    char c;
    int linemax = line.length();
    string curstring;
    record.clear();
    while(linepos < linemax)
    {
        c = line[linepos];
        if(isdigit(c) || c == '.'){
            curstring += c;
        }
        else if(c == delimiter && curstring.size()){
            record.push_back(curstring);
            curstring = "";
        }
        ++linepos;
    }
    if(curstring.size())
        record.push_back(curstring);
    return;
}
 
//CSV reading function===============================================================================
inline float string_to_float(string str){
    int i = 0;
    int len = str.length();
    float sum = 0;
    
    while(i<len){
        if(str[i]=='.') break;
        sum=sum*10+str[i]-'0';
        ++i;
    }
    ++i;
    float t=1,d=1;
    while(i<len){
        d*=0.1;
        t=str[i]-'0';
        sum+=t*d;
        ++i;
    }
    return sum;
}


// These functions get the number of "0" and "1"=====================================================
int totCount0(){
    int count = 0;
    for(int i = 0;i < a.size()-1;i++){
        //cout<<"   "<<a[i][0]<<"    "<<a[i][1]<< endl;
        //cout<<typeid(a[i][0]).name()<<endl; // print out the data type 
        if(a[i][1] == 0){
            ++ count;
        }
    }
    cout<<"number of 0: "<<count<<"\n";
    return count;
}

int totCount1(){
    int count = 0;
    for(int i = 0;i < a.size()-1; ++i){
        //cout<<"   "<<a[i][0]<<"    "<<a[i][1]<< endl;
        //cout<<typeid(a[i][0]).name()<<endl; // print out the data type 
        if(a[i][1] == 1){
            ++ count;
        }  
    }
    cout<<"number of 1: "<<count<<"\n";
    return count;
}


//get range -> vector range===================================================================
inline vector<float> getRange(float count_max, float count_min){
    for(int i = 0; i < a.size()-1; i++){
        if(count_max < a[i][0]){
            count_max = a[i][0];
        }
        if(count_min > a[i][0]){
            count_min = a[i][0];
        }
    }
    //cout<<"max:"<<count_max<<", min: "<<count_min<<" and range: ";
    //cout<<"range: "<<count_max - count_min<<"\n";
    vector<float> vec;
    vec.push_back(count_max);
    vec.push_back(count_min);
    return vec;  
}

//calcuate woe value and return by vector
vector<float> calWoe(vector<int> c0wo, vector<int> c1wo, int tot1, int tot0){
    vector<float> woe_table;
    for(int i = 0; i < c0wo.size(); ++i){
        float woe = log( ((float)c1wo[i]/tot1) / ((float)c0wo[i]/tot0) );
        //cout<<c1wo[i]<<" "<<tot1<<" "<<c0wo[i]<<" "<<tot0<<" "<<endl; 
        woe_table.push_back(woe);
        //cout<<woe<<endl;   
    }
    return woe_table;
}

//printing out function
void print_me(vector<float> woe_table, vector<float> cuts, float max){
    cuts.push_back(max);
    for (int i = 0; i < woe_table.size(); ++i){
        cout<<cuts[i]<<"-"<<cuts[i+1]<<": "<<woe_table[i]<<endl;
    }
}

//this function get the value back to "a"
//This function has O(4n) with 4 cuts as the default value
void swap_value(vector<float> woe_table, vector<float> cuts, float max){
    cuts.push_back(max);
    for (int i = 0; i < a.size()-1; ++i){
        for(int j = 0; j < woe_table.size(); ++j){
            if ((cuts[j]<=a[i][0]) && (a[i][0]<=cuts[j+1])){
                a[i][0] = woe_table[j];
                cout<<a[i][0]<<endl;
                break;
            }          
        }
    }
}

 
//===================================================
//              MIAN FUNCTION START
//===================================================
int main(){
    int segments = 3;  //set how many segments it need
    read("test3.csv");  //set the name of CSV u wanna process
    cout<<"cut into: "<<segments<<"\n";

    // finding the range of existing data
    float count_max = numeric_limits<float>::min();
    float count_min = numeric_limits<float>::max();
   
    int tot1 = totCount1();
    int tot0 = totCount0();

    vector<float> rangeV = getRange(count_max, count_min);
    int range = rangeV[0]-rangeV[1];
    vector<float> cuts = cutit(segments, range, rangeV[1]);

    vector<int> c0wo = getCount0(segments,cuts);
    vector<int> c1wo = getCount1(segments,cuts);
    vector<float> woe_table = calWoe(c0wo,c1wo,tot1,tot0);

    print_me(woe_table, cuts, rangeV[0]);

    swap_value(woe_table, cuts, rangeV[0]);

    return 0;
}

