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

public:
    // all the functions to be used are made public
    bool error = false;
    int offset;
    int last_pc;
    string last_instr;
    branch_prediction(vector<vector<string>>, int choice);
    void branch(vector<string>, int choice);
    long long total_predicted;
    long long correct_predicted;
    int hexatodec(string);
};
#endif
