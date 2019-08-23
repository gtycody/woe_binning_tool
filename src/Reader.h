#ifndef READER_H
#define READER_H

#include <string>
#include <vector>

using namespace std;

class Reader
{
    private:
        string filename;                
        
        vector<vector<float> > matrix;
        vector<float> oneRow;

        void read(string filenami, char delimiter);

        void file_to_string(vector<string> &record, const string& line, char delimiter);

        float string_to_float(string str);

        //True means yes
        bool contain_none;
    
    public:
        
        //constructor
        Reader(string str, char delimiter);
        
        //Destructor
        ~Reader(){};
        
        //return matrix
        vector<vector<float> > get_matrix();

        bool if_contain_none();


};
#endif
