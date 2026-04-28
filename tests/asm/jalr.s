# INIT_REG 2 8
# EXPECT_REG 1 4
# EXPECT_REG 3 0
# EXPECT_PC 8

.text
    jalr x1, 0(x2)
    addi x3, x0, 99
    .word 0
