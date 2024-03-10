#ifndef converter_H
#define converter_H
#include <vector>
#include <string>
#include <utility>
#include <bits/stdc++.h>
using namespace std;
class converter
{
private:
    vector<pair<vector<std::string>, int>> code;

public:
    converter(vector<pair<vector<std::string>, int>>);
    std::string tobinary(std::string, int len);
    std::string tobinary(std::string);
    std::string bintoHex(std::string);
    std::string hextoBin(std::string, int len);
    std::string octToBin(std::string, int len);
    std::string binCheck(std::string, int len);
    void noOfArgumentsError(multimap<int,std::string> &error, int, int, std::string);
    void immCheck(std::string, multimap<int,std::string> &error, int, int);
    void registerCheck(std::string, multimap<int,std::string> &error, int, int);
    void assemblytomachine();
};
#endif
