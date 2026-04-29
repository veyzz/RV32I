# EXPECT_REG 2 0x1fffffff

.text
    li x1, 0xffffffff
    srli x2, x1, 3
    ebreak
