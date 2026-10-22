.text
.globl main

main:
    addi sp, sp, -256
    sw ra, 252(sp)
    sw s0, 248(sp)
    addi s0, sp, 256
    li t0, 2
    li t1, 3
    li t2, 5
    mul t3, t1, t2
    li t1, 7
    div t2, t3, t1
    add t1, t0, t2
    sw t1, -4(s0)
    lw t0, -4(s0)
    li t1, 1
    add t2, t0, t1
    sw t2, -4(s0)
.Lreturn_main:
    lw ra, 252(sp)
    lw s0, 248(sp)
    addi sp, sp, 256
    ret

