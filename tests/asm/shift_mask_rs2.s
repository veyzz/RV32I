# EXPECT_REG 3 256
# EXPECT_REG 5 0x00800000
# EXPECT_REG 6 0xff800000
# EXPECT_PC 0x80000018

.text
    li x1, 1
    li x2, 40
    sll x3, x1, x2
    li x4, 0x80000000
    srl x5, x4, x2
    sra x6, x4, x2
    ebreak
