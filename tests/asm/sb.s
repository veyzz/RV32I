# EXPECT_MEM 0x14 0xab

.text
    li x1, 0x80000000
    li x2, 0x12efcdab
    sb x2, 20(x1)
    ebreak
    .word 0
