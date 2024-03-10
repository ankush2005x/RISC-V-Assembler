#include <bits/stdc++.h>
using namespace std;
#include "parse.h"
#include "converter.h"

ofstream fout;

int main()
{
    // fileInput.open for reading the input file.
    fout.open("output.mc");
    string path = "assembly.s";

    fout << "Data Segment Memory: \n";
    parser tokens(path);
    if (tokens.error == 1)
    {
        fout << tokens.raiseError << "\n";
        return 1;
    }

    fout << "\n\nAssembly Instructions:\n";
    tokens.print();

    fout << "\n\nMachine Code:\n";

    converter obj(tokens.code);
    obj.assemblytomachine();
    fout.close();
    return 0;
}