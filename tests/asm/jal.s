# EXPECT_REG 1 0x80000004
# EXPECT_REG 3 0
# EXPECT_PC 0x80000008

.text
    jal x1, target
    addi x3, x0, 99
target:
    ebreak
