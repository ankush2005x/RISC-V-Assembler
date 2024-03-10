#ifndef converter_H
#define converter_H
#include <vector>
#include <string>
#include <utility>
using namespace std;
//  class converter is made to convert the assembly code to machine code
// it has all the main functions to convert the assembly code to machine code
class converter
{
private:
//  all the variables and containers to be used are made private
    vector<pair<vector<std::string>, int>> code;
    vector<pair<int, string>> errorGenerator;
    map<string, int> m;
    map<string, vector<string>> mo73; // opcode fxn 7 and fxn 3

public:
    // all the functions to be used are made public
    converter(vector<pair<vector<std::string>, int>>);
    std::string tobinary(std::string, int len);
    std::string tobinary(std::string);
    std::string bintoHex(std::string);
    std::string hextoBin(std::string, int len);
    std::string octToBin(std::string, int len);
    std::string binCheck(std::string, int len);

    void basicConverter(pair<vector<string>, int> val);
    void noOfArgumentsError(int, int, std::string);
    int immCheck(std::string, int, int);
    int registerCheck(std::string, int, int);
    int immBoundCheck(std::string, int , int, int);
    long long pow(int a, int b);
    void assemblytomachine();
};
#endif
