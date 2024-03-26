#include <bits/stdc++.h>
using namespace std;
#include "parse.h"
#include "converter.h"

ofstream fout;

int main()
{
    // fileInput.open for reading the input file.
    cout << "Press 1 for Assembly to Machine Code Convertion. \nPress 2 for Branch Table Prediction Analysis.\n";
    int mode;
    cin >> mode;


    fout.open("output.mc");
    string path;
    if(mode == 1){
        path = "assembly.s";
    }else if(mode == 2){
        path = "trace.s";
    }else{
        cout << "Wrong Option Selected. Code Exited.\n";
        return 1;
    }
    fout << "Data Segment Memory: \n";
    parser tokens(path, mode);
    if (tokens.error == 1)
    {
        fout << tokens.raiseError << "\n";
        return 1;
    }

    fout << "\n\nAssembly Instructions:\n";
    tokens.print(mode);

    fout << "\n\nMachine Code:\n";

    if(mode == 1){
        converter obj(tokens.code);
        obj.assemblytomachine();
    }else{
        // Satvik add function call for your branch predictor
    }

    fout.close();
    return 0;
}