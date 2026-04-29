# EXPECT_REG 3 42

.text
    li x1, 100
    li x2, 58
    sub x3, x1, x2
    ebreak
