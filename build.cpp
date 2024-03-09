#include <bits/stdc++.h>
using namespace std;
#include "parse.h"
#include "converter.h"
int main()
{
    string path = "assembly.s";
    parser tokens(path);
    tokens.print();
    converter obj(tokens.code);
    obj.assemblytomachine();
    return 0;
}