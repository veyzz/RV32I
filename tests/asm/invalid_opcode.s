# PC must NOT advance on invalid opcode; registers untouched
# EXPECT_REG 1 99
# EXPECT_PC 0x80000004

.text
    li x1, 99
    .word 0
