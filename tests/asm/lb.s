# EXPECT_REG 2 -1

.text
    lb x2, 8(x1)
    .word 0
    .byte 0xff
    .byte 0, 0, 0
