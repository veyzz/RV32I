# INIT_REG 1 0xffffffe0
# INIT_REG 2 2
# EXPECT_REG 3 -8

.text
    sra x3, x1, x2
    .word 0
