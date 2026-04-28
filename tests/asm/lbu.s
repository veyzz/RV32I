# EXPECT_REG 2 255

.text
    lbu x2, 8(x1)
    .word 0
    .byte 0xff
    .byte 0, 0, 0
