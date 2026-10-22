.text
.globl main

main:
    addi sp, sp, -256
    sw ra, 252(sp)
    sw s0, 248(sp)
    addi s0, sp, 256
    li t0, 15
    li t2, 5
    slli t2, t2, 2
    addi t1, s0, -24
    sub t1, t1, t2
    sw t0, 0(t1)
    li t0, 10
    li t2, 0
    slli t2, t2, 2
    addi t1, s0, -4
    sub t1, t1, t2
    sw t0, 0(t1)
    li t1, 5
    slli t1, t1, 2
    addi t0, s0, -24
    sub t0, t0, t1
    lw t1, 0(t0)
    li t2, 0
    slli t2, t2, 2
    addi t0, s0, -4
    sub t0, t0, t2
    lw t2, 0(t0)
    add t0, t1, t2
    addi t1, s0, -64
    sw t0, 0(t1)
.Lreturn_main:
    lw ra, 252(sp)
    lw s0, 248(sp)
    addi sp, sp, 256
    ret
