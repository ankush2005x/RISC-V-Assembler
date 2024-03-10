#include <bits/stdc++.h>
using namespace std;
#ifndef parse_H
#define parse_H


class parser{
private:
    ifstream fileInput;
    string line;
    int lineNum = 0;
    map <string, int> textLabels;

    int dataLoc = 268435456;         //0x10000000
    // all functions to be used in the constructor
    void removeComments();
    void strip();
    void Character_Check(string word, int lineNum);
    void Label_Error(int lineNum);
    void Label_Exists_Error(int lineNum);
    void labelToOffset();
    void replaceReg();

    void handleData();
    void storeData(vector<string> dataLine, int increase);
    vector<string> convert(bool DorT);
    // making regMap to replace the register names with the register numbers
    map<string, string> regMap = {
        {"ra", "x1"},
        {"sp", "x2"},
        {"gp", "x3"},
        {"tp", "x4"},
        {"t0", "x5"},
        {"t1", "x6"},
        {"t2", "x7"},
        {"s0", "x8"},
        {"fp", "x8"},
        {"s1", "x9"},
        {"a0", "x10"},
        {"a1", "x11"},
        {"a2", "x12"},
        {"a3", "x13"},
        {"a4", "x14"},
        {"a5", "x15"},
        {"a6", "x16"},
        {"a7", "x17"},
        {"s2", "x18"},
        {"s3", "x19"},
        {"s4", "x20"},
        {"s5", "x21"},
        {"s6", "x22"},
        {"s7", "x23"},
        {"s8", "x24"},
        {"s9", "x25"},
        {"s10", "x26"},
        {"s11", "x27"},
        {"t3", "x28"},
        {"t4", "x29"},
        {"t5", "x30"},
        {"t6", "x31"}
    };

public:
    //  all the variables and containers to be used in the constructor
    vector<pair<vector<string>, int>> code;
    vector<vector<string>> dataCode;
    map<string, int> dataLabels;
    bool error = false;
    string raiseError;
    // constructor
    parser(string path);
    void print();
};



#endif