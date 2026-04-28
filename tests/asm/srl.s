# INIT_REG 1 32
# INIT_REG 2 2
# EXPECT_REG 3 8

.text
    srl x3, x1, x2
    .word 0
