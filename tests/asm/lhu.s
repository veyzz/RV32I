# EXPECT_REG 2 65535

.text
    lhu x2, 8(x1)
    .word 0
    .half 0xffff
    .half 0
