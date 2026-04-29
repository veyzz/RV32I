# EXPECT_REG 2 -1

.text
    li x1, 0x80000000
    lb x2, 12(x1)
    .word 0
    .byte 0xff
    .byte 0, 0, 0
