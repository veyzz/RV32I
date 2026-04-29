# EXPECT_REG 3 1

.text
    li x1, 0xffffffff
    li x2, 1
    slt x3, x1, x2
    ebreak
