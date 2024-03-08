#include <bits/stdc++.h>
using namespace std;
#ifndef parse_H
#define parse_H

class parser{
private:
    ifstream fileInput;
    string line;
    int lineNum = 0;

    map <string, int> labels; 

    bool error = false;
    string raiseError;

public:
    vector<pair<vector<string>, int>> code;
    parser(string path);
    void removeComments();
    void strip();
    void Character_Check(string word, int lineNum);
    void Label_Error(int lineNum);
    void Label_Exists_Error(int lineNum);
    void labelToOffset();
    void print();
    vector<string> convert();
};

#endif