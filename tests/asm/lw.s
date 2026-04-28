# EXPECT_REG 2 0x12345678

.text
    lw x2, 8(x1)
    .word 0
    .word 0x12345678
