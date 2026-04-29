# EXPECT_REG 2 65535

.text
    li x1, 0x80000000
    lhu x2, 12(x1)
    .word 0
    .half 0xffff
    .half 0
