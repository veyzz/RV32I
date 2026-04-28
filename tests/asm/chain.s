# INIT_REG 1 10
# INIT_REG 2 32
# EXPECT_REG 3 42
# EXPECT_REG 4 52
# EXPECT_REG 5 20
# EXPECT_PC 12

.text
    add x3, x1, x2
    add x4, x3, x1
    sub x5, x4, x2
    .word 0
