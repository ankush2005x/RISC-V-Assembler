Data Segment Memory: 
0x10000000 0x0
0x10000004 0x1
0x10000008 0xa


Assembly Instructions:
0x0	jal x1 32 
0x4	lw x5 268435456 
0xc	lw x7 268435464 
0x14	beq x0 x0 108 
0x18	lw x6 268435460 
0x20	blt x7 x0 92 
0x24	beq x7 x0 72 
0x28	addi x30 x0 1 
0x2c	beq x7 x30 72 
0x30	addi x2 x2 -12 
0x34	sw x1 0 x2 
0x38	sw x7 4 x2 
0x3c	addi x7 x7 -1 
0x40	jal x1 -32 
0x44	sw x15 8 x2 
0x48	lw x7 4 x2 
0x4c	addi x7 x7 -2 
0x50	jal x1 -48 
0x54	lw x10 8 x2 
0x58	add x15 x15 x10 
0x5c	lw x1 0 x2 
0x60	lw x7 4 x2 
0x64	addi x2 x2 12 
0x68	jalr x0 x1 0 
0x6c	add x15 x0 x5 
0x70	jalr x0 x1 0 
0x74	add x15 x0 x6 
0x78	jalr x0 x1 0 
0x7c	jalr x0 x1 0 


Machine Code:
0x0	0x020000EF
0x4	0x10000297
0x8	0xFFC2A283
0xc	0x10000397
0x10	0xFFC3A383
0x14	0x06000663
0x18	0x10000317
0x1c	0xFEC32303
0x20	0x0403CE63
0x24	0x04038463
0x28	0x00100F13
0x2c	0x05E38463
0x30	0xFF410113
0x34	0x00112023
0x38	0x00712223
0x3c	0xFFF38393
0x40	0xFE1FF0EF
0x44	0x00F12423
0x48	0x00412383
0x4c	0xFFE38393
0x50	0xFD1FF0EF
0x54	0x00812503
0x58	0x00A787B3
0x5c	0x00012083
0x60	0x00412383
0x64	0x00C10113
0x68	0x00008067
0x6c	0x005007B3
0x70	0x00008067
0x74	0x006007B3
0x78	0x00008067
0x7c	0x00008067
