# INIT_REG 2 0xdeadbeef
# EXPECT_MEM 0x8 0xdeadbeef

.text
    sw x2, 8(x1)
    .word 0
