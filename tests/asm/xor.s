# INIT_REG 1 15
# INIT_REG 2 10
# EXPECT_REG 3 5

.text
    xor x3, x1, x2
    .word 0
