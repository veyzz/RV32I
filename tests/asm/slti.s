# INIT_REG 1 0xffffffff
# EXPECT_REG 2 1

.text
    slti x2, x1, 5
    .word 0
