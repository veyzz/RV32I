# INIT_REG 1 0xffffffff
# EXPECT_REG 2 0x1fffffff

.text
    srli x2, x1, 3
    .word 0
