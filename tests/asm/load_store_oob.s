# EXPECT_REG 3 0
# EXPECT_PC 0x80000008

.text
    li x1, 0x80000fff
    lw x2, 0(x1)
    addi x3, x0, 1
    ebreak
