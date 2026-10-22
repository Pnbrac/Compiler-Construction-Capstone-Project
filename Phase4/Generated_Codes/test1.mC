.text
.globl main

main:
    addi sp, sp, -256
    sw ra, 252(sp)
    sw s0, 248(sp)
    addi s0, sp, 256
    li t0, 12
    sw t0, -8(s0)
    lw t0, -8(s0)
    li t1, 10
    add t2, t0, t1
    sw t2, -8(s0)
    li t0, 99
    sw t0, -4(s0)
.Lreturn_main:
    lw ra, 252(sp)
    lw s0, 248(sp)
    addi sp, sp, 256
    ret

