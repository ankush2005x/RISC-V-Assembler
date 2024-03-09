// MyClass.cpp
#include "MyClass.h"
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
typedef long long ll;
// myclass::myclass(vector<vector<std::string>> v, ll store)
// {
//     this->input = v;
//     this->store = store;
// }
// void myclass::DataSegment()
// {
//     for (auto val : input)
//     {
//         if (val[0] == ".word")
//             D_WORD(val, 4);
//         else if (val[0] == ".dword")
//             D_WORD(val, 8);
//         else if (val[0] == ".half")
//             D_WORD(val, 2);
//         else if (val[0] == ".byte")
//             D_WORD(val, 1);
//     }
// }
// void myclass::D_WORD(vector<string> v, ll increase)
// {
//     for (ll i = 1; i < v.size(); i++)
//     {
//         cout << store << v[i];
//         store += increase;
//     }
// }

myclass::myclass(string s)
{
    cout << "this is " << s << endl;
}