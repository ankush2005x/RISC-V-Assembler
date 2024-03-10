
.data
F0: .word 0
F1: .word 1
n: .word 10

.text
main:

    lw x5 F0
    lw x6 F1    
    lw x7 n
    jal x1 fibonacci    
    beq x0 x0 exit

    
fibonacci:
    blt x7 x0 returnNull
    beq x7 x0 returnF0
    addi x30 x0 1
    beq x7 x30 returnF1
    
    addi sp sp -12
    sw x1 0(sp)
    sw x7 4(sp)
    
    addi x7 x7 -1
    
    jal x1 fibonacci
    
    sw x15 8(sp)        #storing result
    
    lw x7 4(sp)
    addi x7 x7 -2
    
    jal x1 fibonacci
    
    lw x10 8(sp)
    add x15 x15 x10
    
    lw x1 0(sp)
    lw x7 4(sp)
    
    addi sp sp 12
    jalr x0 x1 0
    
returnF0:
    add x15 x0 x5
    jalr x0 x1 0
    
returnF1:
    add x15 x0 x6
    jalr x0 x1 0

returnNull:
    jalr x0 x1 0

exit: 
 
