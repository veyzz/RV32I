# EXPECT_REG 2 255

.text
    li x1, 0x80000000
    lbu x2, 12(x1)
    ebreak
    .byte 0xff
    .byte 0, 0, 0
