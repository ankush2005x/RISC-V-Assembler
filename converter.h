#ifndef converter_H
#define converter_H
#include <vector>
#include <string>
#include <utility>
using namespace std;
class converter
{
private:
    vector<pair<vector<std::string>, int>> code;

public:
    converter(vector<pair<vector<std::string>, int>>);
    map<string, int> m;
    map<string, vector<string>> mo73; // opcode fxn 7 and fxn 3
    void instruction_convert(pair<vector<string>, int>);
    std::string tobinary(std::string, int len);
    std::string tobinary(std::string);
    std::string bintoHex(std::string);
    std::string hextoBin(std::string, int len);
    std::string octToBin(std::string, int len);
    std::string binCheck(std::string, int len);
    long long pow(int a, int b);
    void assemblytomachine();
};
#endif
