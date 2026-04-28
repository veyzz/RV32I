# EXPECT_REG 2 -1

.text
    lh x2, 8(x1)
    .word 0
    .half 0xffff
    .half 0
