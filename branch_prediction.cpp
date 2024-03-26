#include <bits/stdc++.h>
using namespace std;

#include "branch_prediction.h"

branch_prediction::branch_prediction(vector<vector<string>> code, int choice)
{
    last_pc = 0;
    offset = 0;
    last_instr = "";
    total_predicted = 0;
    correct_predicted = 0;
    for (auto val : code)
    {
        switch (choice)
        {
        case 1:
        case 2:
            branch(val, choice);
            break;
        }
    }
    if (total_predicted != 0)
        cout << "accuracy when the branch is always taken : " << ((correct_predicted * 1.0) / total_predicted) * 100 << "%" << endl;
    else
        cout << "No branches are present in the code" << endl;
}
void branch_prediction::branch(vector<string> line, int choice)
{
    string this_instr = line[4];
    bool instr_check = false;
    vector<string> branch_instructions = {
        "beq",
        "beqz",
        "bne",
        "blt",
        "bge",
        "bltu",
        "bgeu",
        "bnez",
        "bneu",
        "jal"};
    for (auto val : branch_instructions)
    {
        if (last_instr == val)
        {
            instr_check = true;
            break;
        }
    }
    if (instr_check == true)
    {
        total_predicted++;
        int this_pc = hexatodec(line[2]);
        if (choice == 1)
        {
            if (last_pc + offset == this_pc)
            {
                correct_predicted++;
            }
        }
        else
        {
            if (last_pc + 4 == this_pc)
            {
                correct_predicted++;
            }
        }
    }
    instr_check = false;
    for (auto val : branch_instructions)
    {
        if (last_instr == val)
        {
            instr_check = true;
            break;
        }
    }
    if (instr_check == true)
    {
        if (this_instr == "jal")
        {
            offset = stoi(line[6]);
            last_pc = hexatodec(line[2]);
        }
        else
        {
            offset = stoi(line[7]);
            last_pc = hexatodec(line[2]);
        }
    }
    last_instr = this_instr;
}
long long branch_prediction::hexatodec(string hexVal)
{
    if (hexVal.substr(0, 2) == "0x")
        hexVal = hexVal.substr(0, 2);
    int len = hexVal.size();

    // Initializing base value to 1, i.e 16^0
    int base = 1;

    long long dec_val = 0;
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