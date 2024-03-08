#include <bits/stdc++.h>
using namespace std;
#include "parse.h"



int main(){
    string path = "assembly.s";
    parser tokens(path);
    tokens.print();
    
    return 0;
}