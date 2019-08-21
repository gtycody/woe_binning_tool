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

        void read(string filename);

        void file_to_string(vector<string> &record, const string& line, char delimiter);
        float string_to_float(string str);

    
    public:
        //constructor
        Reader(string str);
        
        //Destructor
        ~Reader();
        
        //return matrix
        vector<vector<float> > get_matrix();
};
#endif
