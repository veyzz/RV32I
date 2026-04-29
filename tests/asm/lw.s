# EXPECT_REG 2 0x12345678

.text
    li x1, 0x80000000
    lw x2, 12(x1)
    .word 0
    .word 0x12345678
