# INIT_REG 1 1
# INIT_REG 2 0xffffffff
# EXPECT_REG 3 1

.text
    sltu x3, x1, x2
    .word 0
