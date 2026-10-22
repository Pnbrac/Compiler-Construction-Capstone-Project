.text
.globl main

main:
    addi sp, sp, -256
    sw ra, 252(sp)
    sw s0, 248(sp)
    addi s0, sp, 256
    li t0, 0
    addi t1, s0, -4
    sw t0, 0(t1)
.Lfor0:
    addi t0, s0, -4
    lw t1, 0(t0)
    li t0, 10
    slt t2, t1, t0
    beqz t2, .Lendfor0
    li t0, 10
    addi t1, s0, -4
    sw t0, 0(t1)
    addi t0, s0, -4
    lw t1, 0(t0)
    li t0, 1
    add t2, t1, t0
    addi t0, s0, -4
    sw t2, 0(t0)
    j .Lfor0
.Lendfor0:
.Lreturn_main:
    lw ra, 252(sp)
    lw s0, 248(sp)
    addi sp, sp, 256
    ret

