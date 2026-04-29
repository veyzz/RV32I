# EXPECT_MEM 0x14 0xbeef

.text
    li x1, 0x80000000
    li x2, 0xdeadbeef
    sh x2, 20(x1)
    ebreak
    .word 0
