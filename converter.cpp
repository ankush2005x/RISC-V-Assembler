#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include "converter.h"
#include <bitset>
using namespace std;

converter::converter(vector<pair<vector<std::string>, int>> code)
{
    this->code = code;
}
long long converter::pow(int a, int b)
{
    long long num = 1;
    for (int i = 0; i < b; i++)
    {
        num *= a;
    }
    return num;
}
string converter::tobinary(string x)
{
    int n = x.length();
    long long num = 0;
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
string converter::tobinary(string x, int len)
{
    int n = x.length();
    long long num = 0;
    if (x[0] != '-')
    {
        for (int i = 0; i < n; i++)
        {
            num += (x[i] - '0') * pow(10, n - i - 1);
        }
        if (num > pow(2, len) - 1)
        {
        }
        string binary = "";
        while (num > 0)
        {
            binary = to_string(num % 2) + binary;
            num = num / 2;
        }
        string binary2 = "";
        for (int i = 1; i <= len - binary.size(); i++)
        {
            binary2 = binary2 + "0";
        }
        binary = binary2 + binary;
        return binary;
    }
    else
    {
        x = x.substr(1);
        for (int i = 0; i < n - 1; i++)
        {
            num += (x[i] - '0') * pow(10, n - i - 2);
        }
        num = pow(2, len) - num;
        string binary = "";
        while (num > 0)
        {
            binary = to_string(num % 2) + binary;
            num = num / 2;
        }
        return binary;
    }
}
string converter::bintoHex(string x)
{
    int n = x.length();
    long long num = 0;
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
    while (hex.size() < 8)
    {
        hex = "0" + hex;
    }
    hex = "0x" + hex;
    return hex;
}
string converter::hextoBin(string x, int len)
{
    int n = x.length();
    string binary = "";
    for (int i = 0; i < n; i++)
    {
        string bin = "";
        if (x[i] >= '0' and x[i] <= '9')
        {
            bin += tobinary(to_string(x[i] - '0'));
        }
        else if (x[i] >= 'a' and x[i] <= 'f')
        {
            bin += tobinary(to_string(x[i] - 'a' + 10));
        }
        else if (x[i] >= 'A' and x[i] <= 'F')
        {
            bin += tobinary(to_string(x[i] - 'A' + 10));
        }
        while (bin.size() < 4)
        {
            bin = "0" + bin;
        }
        binary += bin;
    }
    if (binary.size() > len)
    {
        binary = binary.substr(binary.size() - len);
    }
    string binary2 = "";
    for (int i = 0; i < len - binary.size(); i++)
    {
        binary2 = binary2 + "0";
    }
    binary = binary2 + binary;
    return binary;
}
string converter::octToBin(string x, int len)
{
    int n = x.length();
    string binary = "";
    for (int i = 0; i < n; i++)
    {
        string bin = tobinary(to_string(x[i] - '0'));
        while (bin.size() < 3)
        {
            bin = "0" + bin;
        }
        binary += bin;
    }
    string binary2 = "";
    for (int i = 1; i <= len - binary.size(); i++)
    {
        binary2 = binary2 + "0";
    }
    binary = binary2 + binary;
    return binary;
}
string converter::binCheck(string x, int len)
{
    if (x.size() == 1)
    {
        x = tobinary(x, len);
    }
    else
    {
        if (x[0] == '0' and (x[1] == 'x' or x[1] == 'X'))
        {
            x = x.substr(2);
            x = hextoBin(x, len);
        }
        else if (x[0] == '0' and (x[1] == 'b' or x[1] == 'B'))
        {
            x = x.substr(2);
        }
        else if (x[0] == '0' and (x[1] == 'o' or x[1] == 'O'))
        {
            x = x.substr(2);
            x = octToBin(x, len);
        }
        else
        {
            x = tobinary(x, len);
        }
    }
    return x;
}
int converter::registerCheck(string x, int line, int pos)
{
    if (x[0] != 'x')
    {
        errorGenerator.push_back(pair<int, string>(line, "Register not recognized at argument " + to_string(pos)));
        return 1;
    }
    else
    {
        string y = x.substr(1);
        int n = y.length();
        long long num = 0;
        if (n == 0)
        {
            errorGenerator.push_back(pair<int, string>(line, "Register not recognized at argument " + to_string(pos)));
            return 1;
        }
        else
            for (int i = 0; i < n; i++)
            {
                if (y[i] - '0' >= 0 and y[i] - '0' <= 9)
                {
                    num += (y[i] - '0') * pow(10, n - i - 1);
                }
                else
                {
                    errorGenerator.push_back(pair<int, string>(line, "Register not recognized at argument " + to_string(pos)));
                    return 1;
                }
            }
        if (num > 31)
        {
            errorGenerator.push_back(pair<int, string>(line, "Register number out of range at argument " + to_string(pos)));
            return 1;
        }
    }
    return 0;
}
int converter::immCheck(string x, int line, int pos)
{
    if (x.size() == 1)
    {
        if (x[0] >= '0' and x[0] <= '9')
        {
        }
        else
        {
            errorGenerator.push_back(pair<int, string>(line, "Invalid immediate at argument " + to_string(pos)));
            return 1;
        }
    }
    else if (x[0] == '0' and (x[1] == 'x' or x[1] == 'X'))
    {
        x = x.substr(2);
        int n = x.length();
        if (n == 0)
        {
            errorGenerator.push_back(pair<int, string>(line, "Invalid hex immediate at argument " + to_string(pos)));
            return 1;
        }
        for (int i = 0; i < n; i++)
        {
            if (x[i] >= '0' and x[i] <= '9')
            {
                continue;
            }
            else if (x[i] >= 'A' and x[i] <= 'F')
            {
                continue;
            }
            else if (x[i] >= 'a' and x[i] <= 'f')
            {
                continue;
            }
            else
            {
                errorGenerator.push_back(pair<int, string>(line, "Invalid hex immediate at argument " + to_string(pos)));
                return 1;
            }
        }
    }
    else if (x[0] == '0' and (x[1] == 'b' or x[1] == 'B'))
    {
        x = x.substr(2);
        int n = x.length();
        if (n == 0)
        {
            errorGenerator.push_back(pair<int, string>(line, "Invalid binary immediate at argument " + to_string(pos)));
            return 1;
        }
        for (int i = 0; i < n; i++)
        {
            if (x[i] == '0' or x[i] == '1')
            {
                continue;
            }
            else
            {
                errorGenerator.push_back(pair<int, string>(line, "Invalid binary immediate at argument " + to_string(pos)));
                return 1;
            }
        }
    }
    else if (x[0] == '0' and (x[1] == 'o' or x[1] == 'O'))
    {
        x = x.substr(2);
        int n = x.length();
        if (n == 0)
        {
            errorGenerator.push_back(pair<int, string>(line, "Invalid octal immediate at argument " + to_string(pos)));
            return 1;
        }
        for (int i = 0; i < n; i++)
        {
            if (x[i] >= '0' and x[i] <= '7')
            {
                continue;
            }
            else
            {
                errorGenerator.push_back(pair<int, string>(line, "Invalid octal immediate at argument " + to_string(pos)));
                return 1;
            }
        }
    }
    else
    {
        if (x[0] == '-')
        {
            x = x.substr(1);
        }
        int n = x.length();
        for (int i = 0; i < n; i++)
        {
            if (x[i] >= '0' and x[i] <= '9')
            {
                continue;
            }
            else
            {
                errorGenerator.push_back(pair<int, string>(line, "Invalid decimal immediate at argument " + to_string(pos)));
                return 1;
            }
        }
    }
    return 0;
}
int converter::immBoundCheck(string x, int len, int line, int pos)
{
    int num = 0;
    int n = x.length();
    if (n == 1)
    {
        return 0;
    }
    else
    {
        if (x[0] == '0' and (x[1] == 'o' or x[1] == 'O'))
        {
            x = x.substr(2);
            n = x.length();
            for (int i = 0; i < n; i++)
            {
                num += (x[i] - '0') * pow(8, n - i - 1);
            }
        }
        else if (x[0] == '0' and (x[1] == 'b' or x[1] == 'B'))
        {
            x = x.substr(2);
            n = x.length();
            for (int i = 0; i < n; i++)
            {
                num += (x[i] - '0') * pow(2, n - i - 1);
            }
        }
        else if (x[0] == '0' and (x[1] == 'x' or x[1] == 'X'))
        {
            x = x.substr(2);
            n = x.length();
            for (int i = 0; i < n; i++)
            {
                if (x[i] >= '0' and x[i] <= '9')
                {
                    num += ((int)x[i] - 48) * pow(16, n - i - 1);
                }
                else if (x[i] >= 'a' and x[i] <= 'f')
                {
                    num += (((int)x[i] - 97 + 10) * pow(16, n - i - 1));
                }
                else if (x[i] >= 'A' and x[i] <= 'F')
                {
                    num += (((int)x[i] - 65) + 10) * pow(16, n - i - 1);
                }
            }
        }
        else
        {
            int f = 0;
            if (x[0] == '-')
            {
                f = 1;
                x = x.substr(1);
                n = x.length();
            }
            for (int i = 0; i < n; i++)
            {
                num += (x[i] - '0') * pow(10, n - i - 1);
            }
            if (f == 1)
            {
                num = -1 * num;
            }
        }
        if (num > pow(2, len - 1) - 1 or num < -1 * pow(2, len - 1))
        {
            errorGenerator.push_back(pair<int, string>(line, "Immediate out of range at argument " + to_string(pos)));
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
void converter::noOfArgumentsError(int line, int n, string x)
{
    errorGenerator.push_back(pair<int, string>(line, "Number of arguments for instruction " + x + " is not equal to " + to_string(n)));
}
void converter::assemblytomachine()
{
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
    for (auto val : code)
    {
        string machineCodeBin = "";
        string y = (val.first)[0];
        string rd = "", r1 = "", r2 = "", imm = "";
        if (m[y] == 1) // 1 for r type
        {
            if (val.first.size() - 1 != 3)
                noOfArgumentsError(val.second, 3, y);
            else
            {
                string opc = mo73[y][0];
                string x = (val.first)[1].substr(1);
                int e1 = registerCheck((val.first)[1], val.second, 1);
                if (e1 == 0)
                    rd = tobinary(x, 5);
                x = (val.first)[2].substr(1);
                int e2 = registerCheck((val.first)[2], val.second, 2);
                if (e2 == 0)
                    r1 = tobinary(x, 5);
                string fxn7 = mo73[y][1];
                string fxn3 = mo73[y][2];
                x = (val.first)[3].substr(1);
                int e3 = registerCheck((val.first)[3], val.second, 3);
                if (e3 == 0)
                    r2 = tobinary(x, 5);
                if (e1 == 0 and e2 == 0 and e3 == 0)
                    machineCodeBin = fxn7 + r2 + r1 + fxn3 + rd + opc;
            }
        }
        else if (m[y] == 2) // 2 for I type with imm after rs1
        {
            if (val.first.size() - 1 != 3)
                noOfArgumentsError(val.second, 3, y);
            else
            {
                string opc = mo73[y][0];
                string x = (val.first)[1].substr(1);
                int e1 = registerCheck((val.first)[1], val.second, 1);
                if (e1 == 0)
                    rd = tobinary(x, 5);
                x = (val.first)[2].substr(1);
                int e2 = registerCheck((val.first)[2], val.second, 2);
                if (e2 == 0)
                    r1 = tobinary(x, 5);
                string fxn3 = mo73[y][1];
                x = (val.first)[3];
                int e3 = immCheck(x, val.second, 3);
                int e4 = 0;
                if (e3 == 0)
                {
                    imm = binCheck(x, 12);
                    e4 = immBoundCheck(x, 12, val.second, 3);
                }
                if (e1 == 0 and e2 == 0 and e3 == 0 and e4 == 0)
                    machineCodeBin = imm + r1 + fxn3 + rd + opc;
            }
        }
        else if (m[y] == 3) // 3 for I type with imm before rs1
        {
            if (val.first.size() - 1 != 3)
                noOfArgumentsError(val.second, 3, y);
            else
            {
                string opc = mo73[y][0];
                string x = (val.first)[1].substr(1);
                int e1 = registerCheck((val.first)[1], val.second, 1);
                if (e1 == 0)
                    rd = tobinary(x, 5);
                x = (val.first)[2];
                int e4 = 0;
                int e2 = immCheck(x, val.second, 2);
                if (e2 == 0)
                {
                    imm = binCheck(x, 12);
                    e4 = immBoundCheck(x, 12, val.second, 2);
                }
                x = (val.first)[3].substr(1);
                int e3 = registerCheck((val.first)[3], val.second, 3);
                if (e3 == 0)
                    r1 = tobinary(x, 5);
                string fxn3 = mo73[y][1];
                if (e1 == 0 and e2 == 0 and e3 == 0 and e4 == 0)
                    machineCodeBin = imm + r1 + fxn3 + rd + opc;
            }
        }
        else if (m[y] == 4) // 4 for S type
        {
            if (val.first.size() - 1 != 3)
                noOfArgumentsError(val.second, 3, y);
            else
            {
                string opc = mo73[y][0];
                string x = (val.first)[1].substr(1);
                int e1 = registerCheck((val.first)[1], val.second, 1);
                if (e1 == 0)
                    r1 = tobinary(x, 5);
                x = (val.first)[2];
                int e4 = 0;
                int e2 = immCheck(x, val.second, 2);
                if (e2 == 0)
                {
                    imm = binCheck(x, 12);
                    e4 = immBoundCheck(x, 12, val.second, 2);
                }
                x = (val.first)[3].substr(1);
                int e3 = registerCheck((val.first)[3], val.second, 3);
                if (e3 == 0)
                    r2 = tobinary(x, 5);
                string fxn3 = mo73[y][1];
                if (e1 == 0 and e2 == 0 and e3 == 0 and e4 == 0)
                    machineCodeBin = imm.substr(0, 7) + r1 + r2 + fxn3 + imm.substr(7, 5) + opc;
            }
        }
        else if (m[y] == 5) // 5 for SB type
        {
            if (val.first.size() - 1 != 3)
                noOfArgumentsError(val.second, 3, y);
            else
            {
                string opc = mo73[y][0];
                string x = (val.first)[1].substr(1);
                int e1 = registerCheck((val.first)[1], val.second, 1);
                if (e1 == 0)
                    r1 = tobinary(x, 5);
                x = (val.first)[2].substr(1);
                int e2 = registerCheck((val.first)[2], val.second, 2);
                if (e2 == 0)
                    r2 = tobinary(x, 5);
                x = (val.first)[3];
                int e4 = 0;
                int e3 = immCheck(x, val.second, 3);
                if (e3 == 0)
                {
                    imm = binCheck(x, 13);
                    e4 = immBoundCheck(x, 13, val.second, 3);
                }
                string fxn3 = mo73[y][1];
                if (e1 == 0 and e2 == 0 and e3 == 0 and e4 == 0)
                    machineCodeBin = imm.substr(0, 1) + imm.substr(2, 6) + r2 + r1 + fxn3 + imm.substr(8, 4) + imm.substr(1, 1) + opc;
            }
        }
        else if (m[y] == 6) // 6 for U type
        {
            if (val.first.size() - 1 != 2)
                noOfArgumentsError(val.second, 2, y);
            else
            {
                string opc = mo73[y][0];
                string x = (val.first)[1].substr(1);
                int e1 = registerCheck((val.first)[1], val.second, 1);
                if (e1 == 0)
                    rd = tobinary(x, 5);
                x = (val.first)[2];
                int e2 = immCheck(x, val.second, 2);
                int e4 = 0;
                if (e2 == 0)
                {
                    imm = binCheck(x, 20);
                    e4 = immBoundCheck(x, 20, val.second, 2);
                }
                if (e1 == 0 and e2 == 0 and e4 == 0)
                    machineCodeBin = imm + rd + opc;
            }
        }
        else if (m[y] == 7) // 7 for UJ type
        {
            if (val.first.size() - 1 != 2)
                noOfArgumentsError(val.second, 2, y);
            else
            {
                string opc = mo73[y][0];
                string x = (val.first)[1].substr(1);
                int e1 = registerCheck((val.first)[1], val.second, 1);
                if (e1 == 0)
                    rd = tobinary(x, 5);
                x = (val.first)[2];
                int e4 = 0;
                int e2 = immCheck(x, val.second, 2);
                if (e2 == 0)
                {
                    imm = binCheck(x, 21);
                    e4 = immBoundCheck(x, 21, val.second, 2);
                }
                if (e1 == 0 and e2 == 0 and e4 == 0)
                    machineCodeBin = imm.substr(0, 1) + imm.substr(10, 10) + imm.substr(9, 1) + imm.substr(1, 8) + rd + opc;
            }
        }
        else
        {
            errorGenerator.push_back(pair<int, string>(val.second, "Instruction not recognized"));
            continue;
        }
        string machineCodeHex = bintoHex(machineCodeBin);
        std::cout << "0x" << std::hex << val.second;
        std::cout << "\t" << machineCodeHex << "\n";
    }
    if (errorGenerator.size() > 0)
    {
        cout << "Errors are: " << endl;
        for (auto e : errorGenerator)
        {
            cout << "0x" << std::hex << e.first << "\t" << e.second << endl;
        }
    }
}
