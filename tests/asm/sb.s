# sb stores only the low byte of x2
# INIT_REG 2 0x12efcdab
# EXPECT_MEM 0x8 0xab

.text
    sb x2, 8(x1)
    .word 0
