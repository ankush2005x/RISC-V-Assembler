#include <bits/stdc++.h>

using namespace std;
#include "parse.h"

extern ofstream fout;

parser::parser(string path){
    fileInput.open(path);
    fout.open("output.mc");
    if(!fileInput.is_open() || !fout.is_open()){
        error = 1;
        return;
    }
    bool data = 0;
    bool text = 0;
    vector<string> dataSeg;
    vector<string> textSeg;

    while(getline(fileInput, line)){
        removeComments();
        strip();
        if(line.size() != 0){
            if(line.find(".data") == 0){
                data = 1;
                text = 0;
            }else if(line.find(".text") == 0){
                data = 0;
                text = 1;
            }else{
                if(line.find(".data") != string::npos){
                    error = 1;
                    raiseError = "invalid .data position";
                }else if(line.find(".text") != string::npos){
                    error = 1;
                    raiseError = "invalid .text position";
                }else{
                    if(data == 1 && text == 0){
                        dataSeg.push_back(line);
                    }else{
                        textSeg.push_back(line);
                    }
                }
            }
        }
    }
    for(auto dataLines: dataSeg){
        line = dataLines;
        vector<string> dataInstruction = convert(0);
        dataCode.push_back(dataInstruction);
    }
    handleData();
    if(error == 1){
        return;
    }
    for(auto textLines :textSeg){
        line = textLines;
        vector<string> instruction = convert(1);
        if(error){
            return;
        }
        if(!instruction.empty()){
            code.push_back({instruction, lineNum});
            lineNum+=4;
        }
        
    }
    labelToOffset();
    fileInput.close();
}

void parser::handleData(){
    for (auto dataLine : dataCode){
        if (dataLine[1] == ".word")
            storeData(dataLine, 4);
        else if (dataLine[1] == ".dword")
            storeData(dataLine, 8);
        else if (dataLine[1] == ".half")
            storeData(dataLine, 2);
        else if (dataLine[1] == ".byte")
            storeData(dataLine, 1);
        else{
            error = 1;
            raiseError = "Data type is invalid or missing.";
            return;
        }
    }
}

void parser::storeData(vector<string> dataLine, int increase){
    dataLabels[dataLine[0]] = dataLoc;
    for (int i = 2; i < dataLine.size(); i++){
        fout << "0x" << hex << dataLoc << " " << "0x" << stoi(dataLine[i])<< "\n";
        dataLoc += increase;
    }
}

void parser::labelToOffset(){
    int offsetLineNum = 0;
    for(int i=0; i<code.size(); i++){
        code[i].second += offsetLineNum;
        if(code[i].first[0] == "li" || code[i].first[0] == "lw" || code[i].first[0] == "la"){
            offsetLineNum += 4;
            for(int j=1; j<code[i].first.size(); j++){
                if(textLabels[code[i].first[j]] != 0){
                    code[i].first[j] = to_string(textLabels[code[i].first[j]] - code[i].second);
                }else if(dataLabels[code[i].first[j]] != 0){
                    code[i].first[j] = to_string(dataLabels[code[i].first[j]]);
                }
            }
        }else{
            for(int j=0; j<code[i].first.size(); j++){
                if(textLabels[code[i].first[j]] != 0){
                    code[i].first[j] = to_string(textLabels[code[i].first[j]] - code[i].second);
                }else if(dataLabels[code[i].first[j]] != 0){
                    code[i].first[j] = to_string(dataLabels[code[i].first[j]]);
                }
            }

        }
    }

}

void parser::removeComments(){
    for(int i=0; i<(int)line.size(); i++){

        if(line[i]=='#'){
            line = line.substr(0, i);
            break;
        }
    }

}

void parser::Character_Check(string word, int lineNum){
    for(auto x: word){
        if((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || (x>='0' && x<='9') || x == '-'){
            continue;
        }else{
            raiseError = "Invalid Character in Assembly Instruction. \nLine number: " + to_string(lineNum);
            error = 1;
            return;
        }
    }
    return;
}

void parser::Label_Error(int lineNum){
    error = 1;
    raiseError = "Invalid Label Naming. \nLine number: " + to_string(lineNum);
}

void parser::Label_Exists_Error(int lineNum){
    error = 1;
    raiseError = "Duplicate Labels Not Allowed. \nLine number: " + to_string(lineNum);
}

void parser::strip(){
    int start = 0;
    int end = (int)line.size();
    for(int i=0; i<(int)line.size(); i++){
        if(line[i]!=' ' && line[i]!='\n' && line[i]!='\t'){
            start = i;
            break;
        }
    }
    for(int i = (int)line.size() - 1; i>=0; i--){
        if(line[i]!=' ' && line[i]!='\n' && line[i]!='\t'){
            end = i + 1;
            break;
        }
    }
    if(start<end){
        line = line.substr(start, end-start);
    }else{
        line = "";
    }
    
}

vector<string> parser::convert(bool DorT){      // pass 0 for data instructions, 1 for text instructions.
    vector<string> instruction; 
    string word;
    bool valid = 1;
    string labelName = "";
    
    
    
    for(int i=0; i<(int)line.size(); i++){
        
        if(line[i] == ':'){
            if(instruction.size() > 0){
                Label_Error(lineNum);
                return vector<string>();
            }else{
                if(DorT == 0){
                    instruction.push_back(word);
                }else if(DorT == 1){
                    
                    if(textLabels.find(word)==textLabels.end() && dataLabels.find(word)==dataLabels.end()){
                        textLabels[word] = lineNum;
                    }else{
                        Label_Exists_Error(lineNum);
                        return vector<string>();
                    }
                    
                    labelName = word;
                }
                
                word.clear();
            }

        }else if((line[i] == ' ' || line[i] == ',' || line[i] == '\n')){
            if(!word.empty()){
                instruction.push_back(word);
                word.clear();
            }
            
        }else if(line[i] == '(' && DorT == 1){
            if(instruction.size() != 2){
                error = 1;
                raiseError = "Brackets Unexpected at line number: " + to_string(lineNum);
            }else{
                instruction.push_back(word);
                word.clear();
            }
        }else if(line[i] == ')' && DorT == 1){
            if(i == line.size() - 1){
                instruction.push_back(word);
                word.clear();
            }else{
                error = 1;
                raiseError = "Brackets Unexpected at line number: " + to_string(lineNum);
            }
        }else{
            word += line[i];
        }
        
    }
    if(!word.empty()){
        instruction.push_back(word);
        word.clear();
    }
    for(int i=0; i<(int)instruction.size(); i++){
        if(DorT == 0 && i < 2){
            continue;
        }
        Character_Check(instruction[i], lineNum);
        if(error){
            return vector<string>();
        }
    }


    return instruction;
    
}

void parser::print(){
    for(int i=0; i<code.size(); i++){
        fout << "0x" << code[i].second << "\t";
        for(int j=0; j<code[i].first.size(); j++){
            fout << code[i].first[j] << " "; 
        }
        fout << "\n";
    }
}

