# RISC-V-Assembler in C++ with branch prediction results upto 2 bit
#Setup
For Compilation:  
&emsp;**g++ parse.cpp converter.cpp build.cpp branch_prediction.cpp -o my_program**  

Run the program using:  
&emsp;For linux:&emsp;**./my_program**  
&emsp;For windows:&emsp;**my_program.exe**  

# Some Important Points to be taken care of: 
write **octal** numbers as 0oxxxx or 0Oxxxx  
write **hexadecimal** numbers as 0xABC or 0XABC (upper or lower case or mix all types are allowed)  
write **binary** numbers as 0bxxx or 0Bxxx  
Any **error** which is encountered is present at the end of the output  
To add support for any new instruction, add it's opcode, fxn3 and fxn7 in a map and add an if-else condition in the assemblytomachine() function  
