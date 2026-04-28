# INIT_REG 1 100
# INIT_REG 2 58
# EXPECT_REG 3 42

.text
    sub x3, x1, x2
    .word 0
