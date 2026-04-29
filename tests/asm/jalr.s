# EXPECT_REG 1 0x8000000c
# EXPECT_REG 3 0
# EXPECT_PC 0x80000010

.text
    auipc x2, 0
    addi  x2, x2, 16
    jalr  x1, 0(x2)
    addi  x3, x0, 99
    ebreak
