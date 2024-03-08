#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
// will include an external library later on which will be used in the code
// this will provide a multidimensional array using classes and it's functions
// this multidimensional array will contain parsed risc v instructions
using namespace std;
string tobinary(string x)
{
    int n = x.length();
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        num += (x[i] - '0') * pow(10, n - i - 1);
    }
    string binary = "";
    while (num > 0)
    {
        binary = to_string(num % 2) + binary;
        num = num / 2;
    }
    return binary;
}
string binToHex(string x)
{
    int n = x.length();
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        num += (x[i] - '0') * pow(2, n - i - 1);
    }
    string hex = "";
    while (num > 0)
    {
        int rem = num % 16;
        if (rem < 10)
        {
            hex = to_string(rem) + hex;
        }
        else
        {
            hex = char(rem + 55) + hex;
        }
        num = num / 16;
    }
    return hex;
}
string hexToBin(string x)
{
    int n = x.length();
    string binary = "";
    for (int i = 0; i < n; i++)
    {
        if (x[i] >= '0' and x[i] <= '9')
        {
            binary += tobinary(to_string(x[i] - '0'));
        }
        else
        {
            binary += tobinary(to_string(x[i] - 'A' + 10));
        }
    }
    return binary;
}
string octToBin(string x)
{
    int n = x.length();
    string binary = "";
    for (int i = 0; i < n; i++)
    {
        binary += tobinary(to_string(x[i] - '0'));
    }
    return binary;
}
int main()
{
    string arr[5][5]; // multidimensional array
    map<string, int> m;
    m["add"] = 1;
    m["and"] = 1;
    m["or"] = 1;
    m["sll"] = 1;
    m["slt"] = 1;
    m["sra"] = 1;
    m["srl"] = 1;
    m["sub"] = 1;
    m["xor"] = 1;
    m["mul"] = 1;
    m["div"] = 1;
    m["rem"] = 1;
    // I type with imm after rs1
    m["addi"] = 2;
    m["andi"] = 2;
    m["jalr"] = 2;
    m["ori"] = 2;
    // I type with imm before rs1
    m["lb"] = 3;
    m["ld"] = 3;
    m["lh"] = 3;
    m["lw"] = 3;
    // S type with imm before rs1
    m["sb"] = 4;
    m["sd"] = 4;
    m["sh"] = 4;
    m["sw"] = 4;
    // SB type
    m["beq"] = 5;
    m["bne"] = 5;
    m["blt"] = 5;
    m["bge"] = 5;
    // U type
    m["auipc"] = 6;
    m["lui"] = 6;
    // UJ type
    m["jal"] = 7;
    map<string, vector<string>> mo73; // opcode fxn 7 and fxn 3
    // R type
    mo73["add"].push_back("0110011");
    mo73["and"].push_back("0110011");
    mo73["or"].push_back("0110011");
    mo73["sll"].push_back("0110011");
    mo73["slt"].push_back("0110011");
    mo73["sra"].push_back("0110011");
    mo73["srl"].push_back("0110011");
    mo73["sub"].push_back("0110011");
    mo73["xor"].push_back("0110011");
    mo73["mul"].push_back("0110011");
    mo73["div"].push_back("0110011");
    mo73["rem"].push_back("0110011");
    mo73["add"].push_back("0000000");
    mo73["add"].push_back("000");
    mo73["and"].push_back("0000000");
    mo73["and"].push_back("111");
    mo73["or"].push_back("0000000");
    mo73["or"].push_back("110");
    mo73["sll"].push_back("0000000");
    mo73["sll"].push_back("001");
    mo73["slt"].push_back("0000000");
    mo73["slt"].push_back("010");
    mo73["sra"].push_back("0100000");
    mo73["sra"].push_back("101");
    mo73["srl"].push_back("0000000");
    mo73["srl"].push_back("101");
    mo73["sub"].push_back("0100000");
    mo73["sub"].push_back("000");
    mo73["xor"].push_back("0000000");
    mo73["xor"].push_back("100");
    mo73["mul"].push_back("0000001");
    mo73["mul"].push_back("000");
    mo73["div"].push_back("0000001");
    mo73["div"].push_back("100");
    mo73["rem"].push_back("0000001");
    mo73["rem"].push_back("110");
    // I type opcodes
    mo73["addi"].push_back("0010011");
    mo73["andi"].push_back("0010011");
    mo73["ori"].push_back("0010011");
    mo73["lb"].push_back("0000011");
    mo73["ld"].push_back("0000011");
    mo73["lh"].push_back("0000011");
    mo73["lw"].push_back("0000011");
    mo73["jalr"].push_back("1100111");
    // I type fxn 3
    mo73["addi"].push_back("000");
    mo73["andi"].push_back("111");
    mo73["ori"].push_back("110");
    mo73["lb"].push_back("000");
    mo73["ld"].push_back("011");
    mo73["lh"].push_back("001");
    mo73["lw"].push_back("010");
    mo73["jalr"].push_back("000");
    // S type opcodes
    mo73["sb"].push_back("0100011");
    mo73["sd"].push_back("0100011");
    mo73["sh"].push_back("0100011");
    mo73["sw"].push_back("0100011");
    // S type fxn 3
    mo73["sb"].push_back("000");
    mo73["sd"].push_back("011");
    mo73["sh"].push_back("001");
    mo73["sw"].push_back("010");
    // SB type opcodes
    mo73["beq"].push_back("1100011");
    mo73["bne"].push_back("1100011");
    mo73["blt"].push_back("1100011");
    mo73["bge"].push_back("1100011");
    // SB type fxn 3
    mo73["beq"].push_back("000");
    mo73["bne"].push_back("001");
    mo73["blt"].push_back("100");
    mo73["bge"].push_back("101");
    // U type opcodes
    mo73["auipc"].push_back("0010111");
    mo73["lui"].push_back("0110111");
    // UJ type opcodes
    mo73["jal"].push_back("1101111");
    string y = arr[0][0];
    if (m[y] == 1) // 1 for r type
    {
        string opc = mo73[y][0];
        string x = arr[0][1].substr(1);
        string rd = tobinary(x);
        x = arr[0][2].substr(1);
        string r1 = tobinary(x);
        string fxn7 = mo73[y][1];
        string fxn3 = mo73[y][2];
        x = arr[0][3].substr(1);
        string r2 = tobinary(x);
        string machineCodeBin = fxn7 + r1 + r2 + fxn3 + rd + opc;
        string machineCodeHex = binToHex(machineCodeBin);
    }
    else if (m[y] == 2)
    {
        string opc = mo73[y][0];
        string x = arr[0][1].substr(1);
        string rd = tobinary(x);
        x = arr[0][2].substr(1);
        string r1 = tobinary(x);
        string fxn3 = mo73[y][1];
        x = arr[0][3];
        if (x[0] == '0' and (x[1] == 'x' or x[1] == 'X'))
        {
            x = x.substr(2);
            x = hexToBin(x);
        }
        else if (x[0] == '0' and (x[1] == 'b' or x[1] == 'B'))
        {
            x = x.substr(2);
            // x = tobinary(x);
        }
        else if (x[0] == '0' and (x[1] == 'o' or x[1] == 'O'))
        {
            x = x.substr(2);
            x = octToBin(x);
        }
        else
        {
            x = tobinary(x);
        }
        string imm = x;
        string machineCodeBin = imm + r1 + fxn3 + rd + opc;
    }
    else if (m[y] == 3)
    {
        string opc = mo73[y][0];
        string x = arr[0][1].substr(1);
        string rd = tobinary(x);
        x = arr[0][2].substr(1);
        if (x[0] == '0' and (x[1] == 'x' or x[1] == 'X'))
        {
            x = x.substr(2);
            x = hexToBin(x);
        }
        else if (x[0] == '0' and (x[1] == 'b' or x[1] == 'B'))
        {
            x = x.substr(2);
            // x = tobinary(x);
        }
        else if (x[0] == '0' and (x[1] == 'o' or x[1] == 'O'))
        {
            x = x.substr(2);
            x = octToBin(x);
        }
        else
        {
            x = tobinary(x);
        }
        string imm = x;
        x = arr[0][3];
        string r1 = tobinary(x);
        string fxn3 = mo73[y][1];
        string machineCodeBin = imm + r1 + fxn3 + rd + opc;
    }
    else if (m[y] == 4)
    {
        string opc = mo73[y][0];
        string x = arr[0][1].substr(1);
        string r1 = tobinary(x);
        x = arr[0][2].substr(1);
        if (x[0] == '0' and (x[1] == 'x' or x[1] == 'X'))
        {
            x = x.substr(2);
            x = hexToBin(x);
        }
        else if (x[0] == '0' and (x[1] == 'b' or x[1] == 'B'))
        {
            x = x.substr(2);
            // x = tobinary(x);
        }
        else if (x[0] == '0' and (x[1] == 'o' or x[1] == 'O'))
        {
            x = x.substr(2);
            x = octToBin(x);
        }
        else
        {
            x = tobinary(x);
        }
        string imm = x;
        x = arr[0][3].substr(1);
        string r2 = tobinary(x);
        string fxn3 = mo73[y][1];
        string machineCodeBin = imm.substr(5) + r1 + r2 + fxn3 + imm.substr(0, 5) + opc;
    }
    else if (m[y] == 5)
    {
        string opc = mo73[y][0];
        string x = arr[0][1].substr(1);
        string r1 = tobinary(x);
        x = arr[0][2].substr(1);
        string r2 = tobinary(x);
        x = arr[0][3];
        if (x[0] == '0' and (x[1] == 'x' or x[1] == 'X'))
        {
            x = x.substr(2);
            x = hexToBin(x);
        }
        else if (x[0] == '0' and (x[1] == 'b' or x[1] == 'B'))
        {
            x = x.substr(2);
            // x = tobinary(x);
        }
        else if (x[0] == '0' and (x[1] == 'o' or x[1] == 'O'))
        {
            x = x.substr(2);
            x = octToBin(x);
        }
        else
        {
            x = tobinary(x);
        }
        string imm = x;
        string fxn3 = mo73[y][1];
        string machineCodeBin = imm.substr(11) + imm.substr(4, 6) + r2 + r1 + fxn3 + imm.substr(0, 4) + imm.substr(10, 1) + opc;
    }
    else if (m[y] == 6)
    {
        string opc = mo73[y][0];
        string x = arr[0][1].substr(1);
        string rd = tobinary(x);
        x = arr[0][2];
        if (x[0] == '0' and (x[1] == 'x' or x[1] == 'X'))
        {
            x = x.substr(2);
            x = hexToBin(x);
        }
        else if (x[0] == '0' and (x[1] == 'b' or x[1] == 'B'))
        {
            x = x.substr(2);
            // x = tobinary(x);
        }
        else if (x[0] == '0' and (x[1] == 'o' or x[1] == 'O'))
        {
            x = x.substr(2);
            x = octToBin(x);
        }
        else
        {
            x = tobinary(x);
        }
        string imm = x;
        string machineCodeBin = imm + rd + opc;
    }
    else if (m[y] == 7)
    {
        string opc = mo73[y][0];
        string x = arr[0][1].substr(1);
        string rd = tobinary(x);
        x = arr[0][2];
        if (x[0] == '0' and (x[1] == 'x' or x[1] == 'X'))
        {
            x = x.substr(2);
            x = hexToBin(x);
        }
        else if (x[0] == '0' and (x[1] == 'b' or x[1] == 'B'))
        {
            x = x.substr(2);
            // x = tobinary(x);
        }
        else if (x[0] == '0' and (x[1] == 'o' or x[1] == 'O'))
        {
            x = x.substr(2);
            x = octToBin(x);
        }
        else
        {
            x = tobinary(x);
        }
        string imm = x;
        string machineCodeBin = imm.substr(19) + imm.substr(0, 10) + imm.substr(10, 1) + imm.substr(11, 8) + rd + opc;
    }
}