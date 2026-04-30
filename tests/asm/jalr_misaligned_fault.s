# EXPECT_REG 2 0
# EXPECT_PC 0x80000008

.text
    lui   x1, 0x80000
    addi  x1, x1, 3
    jalr  x0, 0(x1)
    addi  x2, x0, 1
    ebreak
