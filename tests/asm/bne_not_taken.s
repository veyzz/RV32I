# EXPECT_REG 3 99
# EXPECT_PC 0x80000010

.text
    li x1, 5
    li x2, 5
    bne x1, x2, target
    addi x3, x0, 99
target:
    .word 0
