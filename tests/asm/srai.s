# EXPECT_REG 2 -1

.text
    li x1, 0xffffffff
    srai x2, x1, 3
    ebreak
