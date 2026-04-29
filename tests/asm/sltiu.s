# EXPECT_REG 2 0

.text
    li x1, 0xffffffff
    sltiu x2, x1, 5
    ebreak
