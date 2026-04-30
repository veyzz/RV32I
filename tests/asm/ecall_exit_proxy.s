# EXPECT_REG 10 7
# EXPECT_REG 3 0
# EXPECT_PC 0x80000008

.text
    li a0, 7
    li a7, 93
    ecall
    addi x3, x0, 1
    ebreak
