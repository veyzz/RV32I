# INIT_REG 1 1
# INIT_REG 2 5
# EXPECT_REG 3 32

.text
    sll x3, x1, x2
    .word 0
