# EXPECT_REG 1 0x8000000c
# EXPECT_REG 3 7
# EXPECT_PC 0x80000014

.text
    auipc x2, 0
    addi  x2, x2, 17
    jalr  x1, 0(x2)
    addi  x3, x0, 99
    addi  x3, x0, 7
    .word 0
