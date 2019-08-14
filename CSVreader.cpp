#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <typeinfo>


using namespace std;
 
vector<vector<float> >a;  //二维数组存储读入变量
vector<float> b;
 
inline void file_to_string(vector<string> &record, const string& line, char delimiter);
inline float string_to_float(string str);
 
void read(){
    vector<string> row;
    string line;
    string filename;

    ifstream in("test3.csv"); 

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


int main(){
    read();
    cout<<"total number of data:"<<a.size();
    cout<<"\n";
    int count_1 = 0;
    int count_0 = 0;
    for(int i = 0;i < a.size()-1;i++){
        cout<<"   "<<a[i][0]<<"    "<<a[i][1]<<"  "<< a[i][2];
        cout<<typeid(a[i][0]).name()<<endl;
        if(a[i][1] == 1){
            ++ count_1;
        }else{
            ++ count_0;   
        }
        //cout<<count_1;
    }
    cout<<"number of 1: "<<count_1<<"\n";
    cout<<"number of 0: "<<count_0<<"\n";

    return 0;
}
 
