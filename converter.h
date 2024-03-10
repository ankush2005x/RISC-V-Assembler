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
    std::string tobinary(std::string, int len);
    std::string tobinary(std::string);
    std::string bintoHex(std::string);
    std::string hextoBin(std::string, int len);
    std::string octToBin(std::string, int len);
    std::string binCheck(std::string, int len);
    void assemblytomachine();
};
#endif
