#include <vector>
#include <string>
#include <utility>
#include <bits/stdc++.h>
using namespace std;
#ifndef branch_prediction_H
#define branch_prediction_H

//  class converter is made to convert the assembly code to machine code
// it has all the main functions to convert the assembly code to machine code
class branch_prediction
{
private:
    ifstream fileInput;
    string line;
    bool oneBit;
    int twoBit;
    int offset;
    long long last_pc;
    bool last_instr;
    bool error = false;
    long long hexatodec(string);
    
    void branch(vector<string>, int choice);
    void print(int choice);

public:
    branch_prediction(vector<vector<string>>);
    long long total_predicted;
    long long correct_predicted;
    map<long long, tuple<long long, pair<int, int>, int, int>> BTB;
    map<long long, vector<pair<int, int>>> BH;    
};
#endif
