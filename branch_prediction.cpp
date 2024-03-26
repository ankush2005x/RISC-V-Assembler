#include <bits/stdc++.h>
using namespace std;

#include "branch_prediction.h"

branch_prediction::branch_prediction(vector<vector<string>> code)
{
    oneBit = false;
    twoBit = 0;

    last_pc = 0;
    offset = 0;
    last_instr = "";
    total_predicted = 0;
    correct_predicted = 0;
    for (auto val : code)
    {
        branch(val, 1);
    }
    cout << "\nBRANCH ALWAYS TAKEN" << endl;
    if (total_predicted != 0)
        cout << "\tAccuracy : " << ((correct_predicted * 1.0) / total_predicted) * 100 << "%" << endl;
    else
        cout << "\tNo branches are present in the code" << endl;

    total_predicted = 0;
    correct_predicted = 0;
    cout << "\nBRANCH ALWAYS NOT TAKEN" << endl;
    for (auto val : code)
    {
        branch(val, 2);
    }
    if (total_predicted != 0)
        cout << "\tAccuracy : " << ((correct_predicted * 1.0) / total_predicted) * 100 << "%" << endl;
    else
        cout << "\tNo branches are present in the code" << endl;

    total_predicted = 0;
    correct_predicted = 0;
    cout << "\n1 BIT BRANCH PREDICTOR" << endl;
    for (auto val : code)
    {
        branch(val, 3);
    }
    if (total_predicted != 0)
        cout << "\tAccuracy : " << ((correct_predicted * 1.0) / total_predicted) * 100 << "%" << endl;
    else
        cout << "\tNo branches are present in the code" << endl;

    total_predicted = 0;
    correct_predicted = 0;
    cout << "\n2 BIT BRANCH PREDICTOR" << endl;
    for (auto val : code)
    {
        branch(val, 4);
    }
    if (total_predicted != 0)
        cout << "\tAccuracy : " << ((correct_predicted * 1.0) / total_predicted) * 100 << "%" << endl;
    else
        cout << "\tNo branches are present in the code" << endl;
}
void branch_prediction::branch(vector<string> line, int choice)
{
    bool this_instr = false;

    if (line.size() == 3)
    {
        if (line[1] != "jal" && line[1] != "jalr" && line[1] != "j" && line[1] != "jr")
        {
            this_instr = true;
        }
    }
    // bool instr_check = false;
    long long this_pc = hexatodec(line[0]);
    // vector<string> branch_instructions = {
    //     "beq",
    //     "beqz",
    //     "bne",
    //     "blt",
    //     "bge",
    //     "bltu",
    //     "bgeu",
    //     "bnez",
    //     "bneu",
    //     "jal"};
    // for (auto val : branch_instructions)
    // {
    //     if (last_instr == val)
    //     {
    //         instr_check = true;
    //         break;
    //     }
    // }
    if (last_instr == true)
    {
        total_predicted++;
        if (choice == 1)
        {
            if (last_pc + offset == this_pc)
            {
                correct_predicted++;
            }
        }
        else if (choice == 2)
        {
            if (last_pc + 4 == this_pc)
            {
                correct_predicted++;
            }
        }else if (choice == 3){
            if(oneBit == false){        //NOT TAKEN
                if (last_pc + 4 == this_pc)
                {
                    correct_predicted++;
                    oneBit = false;
                }else{
                    oneBit = true;
                }  
            }else{
                if (last_pc + offset == this_pc)
                {
                    correct_predicted++;
                    oneBit = true;
                }else{
                    oneBit = false;
                }  
            }

        }else if (choice == 4){
            if(twoBit < 2){        //NOT TAKEN
                if (last_pc + 4 == this_pc)
                {
                    correct_predicted++;
                    twoBit = max(0, twoBit - 1);
                }else{
                    twoBit = twoBit + 1;
                }  
            }else{
                if (last_pc + offset == this_pc)
                {
                    correct_predicted++;
                    twoBit = min(3, twoBit + 1);
                }else{
                    twoBit = twoBit - 1;
                }  
            }
        }
    }
    // instr_check = false;
    // for (auto val : branch_instructions)
    // {
    //     if (last_instr == val)
    //     {
    //         instr_check = true;
    //         break;
    //     }
    // }
    if (this_instr == true)
    {
        if (line[1] != "jal")
        {
            offset = stoi(line[2]);
            last_pc = this_pc;
        }
        BTB[this_pc] = {this_pc + offset, {-1, -1}};
    }
    last_instr = this_instr;
}

long long branch_prediction::hexatodec(string hexVal)
{
    if (hexVal.substr(0, 2) == "0x")
        hexVal = hexVal.substr(2);
    int len = hexVal.size();

    // Initializing base value to 1, i.e 16^0
    //cout << hexVal << " : ";
    long long base = 1;
    long long dec_val = 0;
    for (int i = len - 1; i >= 0; i--)
    {   
        if (hexVal[i] >= '0' && hexVal[i] <= '9')
        {
            //cout << hexVal[i] - '0' << " ";
            dec_val += (hexVal[i] - '0') * base;
            base = base * 16;
        }
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F')
        {
            //cout << hexVal[i] - 'A' + 10 << " ";
            dec_val += (hexVal[i] - 'A' + 10) * base;
            base = base * 16;
        }
        else if (hexVal[i] >= 'a' && hexVal[i] <= 'f')
        {
            //cout << hexVal[i] - 'a' + 10 << " ";
            dec_val += (hexVal[i] - 'a' + 10) * base;
            base = base * 16;
        }
    }
    //cout << "\n";
    return dec_val;
}