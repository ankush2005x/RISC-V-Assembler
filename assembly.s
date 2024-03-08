add x11 x0 x0       # i = 0
#la x7 arr
#lw  x13 length      # length = n
addi x9 x13 -1

for1:
add x12 x0 x0       # j = 0
blt x11 x13 for2    # i < n
beq x0 x0 exit

for2:
bge x12 x9 incF1
slli x10 x12 2
add x14 x7 x10      # &arr[j] = arr + 4*j
lw x15 0(x14)       # load a[i]
lw x16 4(x14)       # load a[i+1]
ble x15 x16 incF2     # if a[i] >= a[i+1]
swap:
sw x15 4(x14)
sw x16 0(x14)
#add x8 x15 x0
#lw x15 0(x16)
#lw x16 0(x8)
incF2:
addi x12 x12 1      # j++
beq x0 x0 for2

incF1: 
addi x11 x11 1      # i++
beq x0 x0 for1
exit: