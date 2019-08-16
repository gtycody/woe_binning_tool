#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <limits> //since MAX and MIN num are recorded in limits


//====================================================
//Since I do not use C++ for a long time
//I Shall not able to finish the job to 
//do the whole woe_binnning tool
//but I'll fo it for a complete columns with all float  
//====================================================

using namespace std;
 
vector<vector<float> >a;  //二维数组存储读入变量
vector<float> b;
 
inline void file_to_string(vector<string> &record, const string& line, char delimiter);
inline float string_to_float(string str);
inline void getCount(float count_0, float count_1);
inline void getRange(float count_max, float count_min);
 
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
inline void file_to_string(vector<string> &record, const string& line, char delimiter)
{
    int linepos=0;
    char c;
    int linemax=line.length();
    string curstring;
    record.clear();
    while(linepos<linemax)
    {
        c = line[linepos];
        if(isdigit(c)||c=='.'){
            curstring+=c;
        }
        else if(c==delimiter&&curstring.size()){
            record.push_back(curstring);
            curstring="";
        }
        ++linepos;
    }
    if(curstring.size())
        record.push_back(curstring);
    return;
}
 
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



// This function getting the count of "0" and "1"
inline void getCount(float count_0, float count_1){
    for(int i = 0;i < a.size()-1;i++){
        cout<<"   "<<a[i][0]<<"    "<<a[i][1]<< endl;
        //cout<<typeid(a[i][0]).name()<<endl; // print out the data type 
        if(a[i][1] == 1){
            ++ count_1;
        }else{
            ++ count_0;   
        }
        //cout<<count_1;
    }
    cout<<"number of 1: "<<count_1<<"\n";
    cout<<"number of 0: "<<count_0<<"\n";
    return ;
}

inline void getRange(float count_max, float count_min){
    for(int i = 0; i < a.size()-1; i++){
        if(count_max < a[i][0]){
            count_max = a[i][0];
        }
        if(count_min > a[i][0]){
            count_min = a[i][0];
        }
    }
    cout<<"max:"<<count_max<<", min: "<<count_min<<" and range: ";
    cout<<"range: "<<count_max - count_min<<"\n";
}
 
//===================================================
//              MIAN FUNCTION START
//===================================================
int main(){





    read("test3.csv");
    cout<<"total number of data:"<<a.size();
    cout<<"\n";
    float count_1 = 0;
    float count_0 = 0;

    // finding the range of existing data
    float count_max = numeric_limits<float>::min();
    float count_min = numeric_limits<float>::max();
    getCount(count_0, count_1);
    getRange(count_max, count_min);
    return 0;
}


