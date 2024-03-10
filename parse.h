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
    void removeComments();
    void strip();
    void Character_Check(string word, int lineNum);
    void Label_Error(int lineNum);
    void Label_Exists_Error(int lineNum);
    void labelToOffset();

    void handleData();
    void storeData(vector<string> dataLine, int increase);
    vector<string> convert(bool DorT);

public:
    
    vector<pair<vector<string>, int>> code;
    vector<vector<string>> dataCode;
    map<string, int> dataLabels; 
    bool error = false;
    string raiseError;

    parser(string path);
    void print();
};



#endif