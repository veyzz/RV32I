# INIT_REG 1 12
# INIT_REG 2 10
# EXPECT_REG 3 14

.text
    or x3, x1, x2
    .word 0
