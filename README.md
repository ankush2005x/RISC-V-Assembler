# RISC-V-Assembler in C++

To run the test program :enter ./my_program

To run a fresh program :enter the following commands :

g++ -c parse.cpp -o parse.o
g++ -c converter.cpp -o converter.o
g++ -c build.cpp -o build.o
g++ parse.o converter.o build.o -o my_program
