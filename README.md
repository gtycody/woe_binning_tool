1. The main purpose of this project is to provide a convinent way to calculate woe value 
2. The Cpp file should able to complete the woe binning for a completed columns with float as its primiary value
3. The python file is able to do all kind of binning despite the missing data(Nan)
4. However, u know Cython suck!

test1.csv with object columns
test2.csv with a little values in it
test3.csv with 320k * 2 datas all float

----updated 2019-08-19




performed a sturctural change
u could compile with command:
g++ -O3 main.cpp Reader.cpp Calculation.cpp

----updated 2019-08-20


destructor updated 

----updated 2019-08-21


try to perform same process with columns which contains none
becasue the large cost of defining a new struct, We try to swap
Nan value in column with M_PI which is 3.14159
And skip those unique number when performing the Calculation
NOT YET FINISH

----updated 2019-08-23
