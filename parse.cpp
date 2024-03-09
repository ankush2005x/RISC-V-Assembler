#include <bits/stdc++.h>

using namespace std;
#include "parse.h"

parser::parser(string path)
{
    fileInput.open(path);
    if (!fileInput.is_open())
    {
        error = 1;
        return;
    }
    while (getline(fileInput, line))
    {
        vector<string> instruction = convert();
        if (error)
        {
            return;
        }
        if (!instruction.empty())
        {
            code.push_back({instruction, lineNum});
            lineNum += 4;
        }
    }
    labelToOffset();
}

void parser::labelToOffset()
{
    for (int i = 0; i < code.size(); i++)
    {
        for (int j = 0; j < code[i].first.size(); j++)
        {
            if (labels[code[i].first[j]] != 0)
            {
                code[i].first[j] = to_string(labels[code[i].first[j]] - code[i].second);
            }
        }
    }
}

void parser::removeComments()
{
    for (int i = 0; i < (int)line.size(); i++)
    {

        if (line[i] == '#')
        {
            line = line.substr(0, i);
            break;
        }
    }
}

void parser::Character_Check(string word, int lineNum)
{
    for (auto x : word)
    {
        if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || (x >= '0' && x <= '9') || x == '-')
        {
            continue;
        }
        else
        {
            raiseError = "Invalid Character in Assembly Instruction. \nLine number: " + to_string(lineNum);
            error = 1;
            return;
        }
    }
    return;
}

void parser::Label_Error(int lineNum)
{
    error = 1;
    raiseError = "Invalid Label Naming. \nLine number: " + to_string(lineNum);
}

void parser::Label_Exists_Error(int lineNum)
{
    error = 1;
    raiseError = "Duplicate Labels Not Allowed. \nLine number: " + to_string(lineNum);
}

void parser::strip()
{
    int start = 0;
    int end = (int)line.size();
    for (int i = 0; i < (int)line.size(); i++)
    {
        if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
        {
            start = i;
            break;
        }
    }
    for (int i = (int)line.size() - 1; i >= 0; i--)
    {
        if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
        {
            end = i + 1;
            break;
        }
    }
    line = line.substr(start, end);
}

vector<string> parser::convert()
{
    vector<string> instruction;
    string word;
    bool valid = 1;
    string labelName = "";

    removeComments();

    strip();

    for (int i = 0; i < (int)line.size(); i++)
    {

        if (line[i] == ':')
        {
            if (instruction.size() > 0)
            {
                Label_Error(lineNum);
                return vector<string>();
            }
            else
            {
                if (labels.find(word) == labels.end())
                {
                    labels[word] = lineNum;
                }
                else
                {
                    Label_Exists_Error(lineNum);
                    return vector<string>();
                }

                labelName = word;
                word.clear();
            }
        }
        else if ((line[i] == ' ' || line[i] == ',' || line[i] == '\n'))
        {
            if (!word.empty())
            {
                instruction.push_back(word);
                word.clear();
            }
        }
        else if (line[i] == '(')
        {
            if (instruction.size() != 2)
            {
                error = 1;
                raiseError = "Brackets Unexpected at line number: " + to_string(lineNum);
            }
            else
            {
                instruction.push_back(word);
                word.clear();
            }
        }
        else if (line[i] == ')')
        {
            if (i == line.size() - 1)
            {
                instruction.push_back(word);
                word.clear();
            }
            else
            {
                error = 1;
                raiseError = "Brackets Unexpected at line number: " + to_string(lineNum);
            }
        }
        else
        {
            word += line[i];
        }
    }
    if (!word.empty())
    {
        instruction.push_back(word);
        word.clear();
    }
    for (int i = 0; i < (int)instruction.size(); i++)
    {
        Character_Check(instruction[i], lineNum);
        if (error)
        {
            return vector<string>();
        }
    }

    return instruction;
}

void parser::print()
{
    for (int i = 0; i < code.size(); i++)
    {
        cout << "0x" << hex << code[i].second << "\t";
        for (int j = 0; j < code[i].first.size(); j++)
        {
            cout << code[i].first[j] << " ";
        }
        cout << "\n";
    }
}
