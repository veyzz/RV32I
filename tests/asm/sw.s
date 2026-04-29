# EXPECT_MEM 0x14 0xdeadbeef

.text
    li x1, 0x80000000
    li x2, 0xdeadbeef
    sw x2, 20(x1)
    .word 0
    .word 0
