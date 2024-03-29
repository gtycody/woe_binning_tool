#include "Reader.h"
#include <iostream>
#include <fstream> 
//#include <string> 
//#include <vector>

using namespace std;

//Default Reader Constructor
Reader::Reader(string str, char delimiter)
{
    cout<<"start to read"<<endl;
    contain_none = false;
    filename = str;
    read(filename,delimiter);
    cout<<"contain_none: "<<contain_none<<endl;
    cout<<"read end!"<<endl;
}


//Reader::~Reader(){}

//read csv
void Reader::read(string filename, char delimiter){
    vector<string> row;
    string line;

    ifstream in(filename); 

    if (in.fail()){ 
        cout << "File not found" <<endl; 
        return ; 
    } 
   
    while(getline(in, line)  && in.good() )
    {
        file_to_string(row, line, delimiter);
        if(row.size() == 1)
        {   
            oneRow.push_back(3.14159);
            oneRow.push_back(string_to_float(row[0]));
            contain_none = true;
        }
        else
        {
            oneRow.push_back(string_to_float(row[0]));
            oneRow.push_back(string_to_float(row[1]));
        }
        matrix.push_back(oneRow);
        oneRow.clear();
    }
    in.close();
}

//covert file to string
void Reader::file_to_string(vector<string> &record, const string& line, char delimiter)
{
    int linepos = 0;
    char c;
    int linemax = line.length();
    string curstring;
    record.clear();
    
    while(linepos < linemax)
    {
        c = line[linepos];
        if(linepos == 0 && c == delimiter)
        {
            ++linepos;
            continue;
        }          
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
 
//convert string to file
float Reader::string_to_float(string str)
{
    int i = 0;
    int len = str.length();
    float sum = 0;
    
    while(i<len)
    {
        if(str[i] == '.')
        {
            break;
        }
        sum = sum * 10 + str[i]- '0';
        ++i;
    }
    ++i;
    
    float t = 1, d = 1;
    while(i<len)
    {
        d *= 0.1;
        t = str[i] - '0';
        sum += t*d;
        ++i;
    }
    return sum;
}

//return matrix
vector<vector<float> > Reader::get_matrix(){
    return matrix;
}

//
bool Reader::if_contain_none()
{
    return contain_none;
}
