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
    fout.close();
    converter obj(tokens.code);
    obj.assemblytomachine();
    
    return 0;
}