# EXPECT_REG 3 42
# EXPECT_REG 4 52
# EXPECT_REG 5 20
# EXPECT_PC 0x80000014

.text
    li x1, 10
    li x2, 32
    add x3, x1, x2
    add x4, x3, x1
    sub x5, x4, x2
    ebreak
