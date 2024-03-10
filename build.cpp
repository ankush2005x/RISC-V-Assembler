#include <bits/stdc++.h>
using namespace std;
#include "parse.h"
#include "converter.h"

ofstream fout;

int main()
{
    
    string path = "assembly.s";
    parser tokens(path);
    if(tokens.error == 1){
        fout << tokens.raiseError << "\n";
        return 1;
    }
    tokens.print();
    converter obj(tokens.code);
    obj.assemblytomachine();
    fout.close();
    return 0;
}