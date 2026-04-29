# EXPECT_REG 2 -1

.text
    li x1, 0x80000000
    lh x2, 12(x1)
    .word 0
    .half 0xffff
    .half 0
