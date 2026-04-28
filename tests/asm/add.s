# INIT_REG 1 10
# INIT_REG 2 32
# EXPECT_REG 3 42

.text
    add x3, x1, x2
    .word 0
