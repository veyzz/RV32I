# INIT_REG 1 0xffffffff
# INIT_REG 2 1
# EXPECT_REG 3 1

.text
    slt x3, x1, x2
    .word 0
