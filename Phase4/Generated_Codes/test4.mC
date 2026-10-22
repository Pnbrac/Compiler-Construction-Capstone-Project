.text
.globl main

main:
    addi sp, sp, -256
    sw ra, 252(sp)
    sw s0, 248(sp)
    addi s0, sp, 256
    li t0, 10
    li t1, 15
    slt t2, t0, t1
    beqz t2, .Lelse0
    li t0, 0
    sw t0, -4(s0)
    j .Lendif0
.Lelse0:
    li t0, 5
    sw t0, -4(s0)
.Lendif0:
.Lreturn_main:
    lw ra, 252(sp)
    lw s0, 248(sp)
    addi sp, sp, 256
    ret

