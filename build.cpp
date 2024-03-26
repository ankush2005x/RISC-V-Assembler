#include <bits/stdc++.h>
using namespace std;
#include "parse.h"
#include "converter.h"
#include "branch_prediction.h"

ofstream fout;

int main()
{
    // fileInput.open for reading the input file.
    cout << "Press 1 for Assembly to Machine Code Convertion. \nPress 2 for Branch Table Prediction Analysis.\n";
    int mode;
    cin >> mode;

    fout.open("output.mc");
    string path;
    if (mode == 1)
    {
        path = "assembly.s";
    }
    else if (mode == 2)
    {
        path = "trace.s";
    }
    else
    {
        cout << "Wrong Option Selected. Code Exited.\n";
        return 1;
    }
    parser tokens(path, mode);
    
    if (mode == 1)
    {
        fout << "Data Segment Memory: \n";
        
        if (tokens.error == 1)
        {
            fout << tokens.raiseError << "\n";
            return 1;
        }
        fout << "\n\nAssembly Instructions:\n";
        tokens.print(mode);

        fout << "\n\nMachine Code:\n";
        converter obj(tokens.code);
        obj.assemblytomachine();
    }
    else
    {
        vector<vector<string>> branchData;
        for (auto items : tokens.code)
        {
            branchData.push_back(items.first);
        }
        branch_prediction obj(branchData);
    }

    fout.close();
    return 0;
}
