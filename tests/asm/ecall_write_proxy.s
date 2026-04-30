# EXPECT_REG 10 14
# EXPECT_REG 11 0x8000001c
# EXPECT_PC 0x80000018

.text
    li a0, 1
    auipc a1, 0
    addi a1, a1, 24
    li a2, 14
    li a7, 64
    ecall
    ebreak
    .ascii "Hello, world!\n"
