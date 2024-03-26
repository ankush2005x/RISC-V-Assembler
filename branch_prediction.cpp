#include <bits/stdc++.h>
using namespace std;

#include "branch_prediction.h"

branch_prediction::branch_prediction(vector<vector<string>> code)
{
    oneBit = false;
    twoBit = 0;

    last_pc = 0;
    offset = 0;
    last_instr = false;
    total_predicted = 0;
    correct_predicted = 0;
    

    for (auto val : code)
    {
        branch(val, 1);
    }
    cout << "\nBRANCH ALWAYS TAKEN" << "\n";
    if (total_predicted != 0)
        cout << "\tAccuracy : " << ((correct_predicted * 1.0) / total_predicted) * 100 << "%" << "\n";
    else
        cout << "\tNo branches are present in the code" << "\n";

    print(1);
    BTB.clear();
    BH.clear();

    last_pc = 0;
    offset = 0;
    last_instr = false;
    total_predicted = 0;
    correct_predicted = 0;
    cout << "\nBRANCH ALWAYS NOT TAKEN" << "\n";
    for (auto val : code)
    {
        branch(val, 2);
    }
    if (total_predicted != 0)
        cout << "\tAccuracy : " << ((correct_predicted * 1.0) / total_predicted) * 100 << "%" << "\n";
    else
        cout << "\tNo branches are present in the code" << "\n";
    
    print(2);
    BTB.clear();
    BH.clear();

    last_pc = 0;
    offset = 0;
    last_instr = false;    
    total_predicted = 0;
    correct_predicted = 0;
    cout << "\n1 BIT BRANCH PREDICTOR" << "\n";
    for (auto val : code)
    {
        branch(val, 3);
    }
    if (total_predicted != 0)
        cout << "\tAccuracy : " << ((correct_predicted * 1.0) / total_predicted) * 100 << "%" << "\n";
    else
        cout << "\tNo branches are present in the code" << "\n";
    
    print(3);
    BTB.clear();
    BH.clear();
    
    last_pc = 0;
    offset = 0;
    last_instr = false;    
    total_predicted = 0;
    correct_predicted = 0;
    cout << "\n2 BIT BRANCH PREDICTOR" << "\n";
    for (auto val : code)
    {
        branch(val, 4);
    }
    if (total_predicted != 0)
        cout << "\tAccuracy : " << ((correct_predicted * 1.0) / total_predicted) * 100 << "%" << "\n";
    else
        cout << "\tNo branches are present in the code" << "\n";
    
    print(4);
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
    
    long long this_pc = hexatodec(line[0]);

    if (last_instr == true)
    {
        total_predicted++;
        if (choice == 1)
        {
            if (last_pc + offset == this_pc)
            {

                get<3>(BTB[last_pc]) = 1;
                correct_predicted++;
            }else{
                get<3>(BTB[last_pc]) = 0;
            }
            BH[last_pc].push_back({1, get<3>(BTB[last_pc])});
        }
        else if (choice == 2)
        {
            if (last_pc + 4 == this_pc)
            {
                get<3>(BTB[last_pc]) = 0;
                correct_predicted++;
            }else{
                get<3>(BTB[last_pc]) = 1;
            }
            BH[last_pc].push_back({0, get<3>(BTB[last_pc])});
        }else if (choice == 3){
            pair<int, int> temp;
            temp.first = oneBit;
            if(oneBit == false){        //NOT TAKEN
                if (last_pc + 4 == this_pc)
                {
                    get<3>(BTB[last_pc]) = 0;
                    correct_predicted++;
                    oneBit = false;
                }else{
                    get<3>(BTB[last_pc]) = 1;
                    oneBit = true;
                }  
            }else{
                if (last_pc + offset == this_pc)
                {
                    get<3>(BTB[last_pc]) = 1;
                    correct_predicted++;
                    oneBit = true;
                }else{
                    get<3>(BTB[last_pc]) = 0;
                    oneBit = false;
                }  
            }
            temp.second = get<3>(BTB[last_pc]);
            BH[last_pc].push_back(temp);
        }else if (choice == 4){
            pair<int, int> temp;
            temp.first = twoBit;
            if(twoBit < 2){        //NOT TAKEN
                if (last_pc + 4 == this_pc)
                {
                    get<3>(BTB[last_pc]) = 0;
                    correct_predicted++;
                    twoBit = max(0, twoBit - 1);
                }else{
                    get<3>(BTB[last_pc]) = 1;
                    twoBit = twoBit + 1;
                }  
            }else{
                if (last_pc + offset == this_pc)
                {
                    get<3>(BTB[last_pc]) = 1;
                    correct_predicted++;
                    twoBit = min(3, twoBit + 1);
                }else{
                    get<3>(BTB[last_pc]) = 0;
                    twoBit = twoBit - 1;
                }  
            }
            temp.second = get<3>(BTB[last_pc]);
            BH[last_pc].push_back(temp);
        }
    }

    if (this_instr == true)
    {
        if (line[1] != "jal" && line[1] != "jalr" && line[1] != "j" && line[1] != "jr")
        {
            offset = stoi(line[2]);
            last_pc = this_pc;
        }
        if(choice == 1){
            BTB[this_pc] = {this_pc + offset, {-1, -1}, 1, -1};
        }else if(choice == 2){
            BTB[this_pc] = {this_pc + offset, {-1, -1}, 0, -1};
        }else if(choice == 3){
            BTB[this_pc] = {this_pc + offset, {-1, (int)oneBit}, oneBit, -1};
        }else if(choice == 4){
            BTB[this_pc] = {this_pc + offset, {twoBit&2, twoBit&1}, twoBit&2, -1};
        }
        
    }
    last_instr = this_instr;
}

void branch_prediction::print(int choice){
    cout << "\n Branch Buffer Table: \n";
    cout << "\nCurrent PC \t Target PC\n";
    for(auto itr: BTB){
        cout << "0x" << hex << itr.first << "\t"<< "0x" << hex << get<0>(itr.second)<<"\n";// << "\t" << get<1>(itr.second).first << get<1>(itr.second).second << "\t" << (get<2>(itr.second) == 1 ? "T" : "NT") << "\t" << (get<3>(itr.second) == 1 ? "T" : "NT") << "\n";
    }
    cout << "\n";
    cout << "\n Branch History Table: \n";
    cout << "\nCurrent PC \t Predicted \t Actual \n";
    for(auto itr: BH){
        cout << "0x" << hex << itr.first << ":"<<"\n";
        for(auto hist: itr.second){
            if(choice!=4){
                cout <<  "\t\t\t" <<(hist.first == 1 ? "T" : "NT") << "\t     " << (hist.second == 1 ? "T" : "NT") << "\n";
            }else{
                if(hist.first == 0){
                    cout << "\t\t Strong NT";
                }else if(hist.first == 1){
                    cout << "\t\t Weakly NT";
                }else if(hist.first == 2){
                    cout << "\t\t Weakly T";
                }else if(hist.first == 3){
                    cout << "\t\t Strong NT";
                }
                cout << "\t     " << (hist.second == 1 ? "T" : "NT") << "\n";
            }
            
        }
    }
    cout << "\n";
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