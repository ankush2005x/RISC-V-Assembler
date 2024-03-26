#include <bits/stdc++.h>
using namespace std;

#include "branch_prediction.h"

branch_prediction::branch_prediction(string path)
{
    fileInput.open(path);
    last_pc = 0;
    offset = 0;
    last_instr = "";
    total_predicted = 0;
    correct_predicted = 0;
    if (!fileInput.is_open())
    {
        error = 1;
        return;
    }
    while (getline(fileInput, line))
    {
        branch_taken(line);
    }
    if (total_predicted != 0)
        cout << "accuracy when the branch is always taken : " << ((correct_predicted * 1.0) / total_predicted) * 100 << "%" << endl;
    else
        cout << "No branches are present in the code" << endl;
}
void branch_prediction::branch_taken(string line)
{
    string this_instr = line.substr(34, 3);
    if (last_instr == "beq" || last_instr == "bne" || last_instr == "blt" || last_instr == "bge")
    {
        total_predicted++;
        int this_pc = hexatodec(line.substr(12, 8));
        if (last_pc + offset == this_pc)
        {
            correct_predicted++;
        }
    }
    if (this_instr == "beq" || this_instr == "bne" || this_instr == "blt" || this_instr == "bge")
    {
        int offset = stoi(line.substr(55));
        last_pc = hexatodec(line.substr(12, 8));
    }
    last_instr = this_instr;
}
int branch_prediction::hexatodec(string hexVal)
{
    int len = hexVal.size();

    // Initializing base value to 1, i.e 16^0
    int base = 1;

    int dec_val = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (hexVal[i] >= '0' && hexVal[i] <= '9')
        {
            dec_val += (int(hexVal[i]) - 48) * base;
            base = base * 16;
        }
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F')
        {
            dec_val += (int(hexVal[i]) - 55) * base;
            base = base * 16;
        }
    }
    return dec_val;
}
int main()
{
    branch_prediction obj("assembly2.s");
}