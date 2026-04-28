# sh stores only the low halfword of x2
# INIT_REG 2 0xdeadbeef
# EXPECT_MEM 0x8 0xbeef

.text
    sh x2, 8(x1)
    .word 0
