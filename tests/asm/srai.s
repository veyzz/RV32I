# INIT_REG 1 0xffffffff
# EXPECT_REG 2 -1

.text
    srai x2, x1, 3
    .word 0
