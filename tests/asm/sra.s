# EXPECT_REG 3 -8

.text
    li x1, 0xffffffe0
    li x2, 2
    sra x3, x1, x2
    ebreak
