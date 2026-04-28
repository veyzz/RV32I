# PC must NOT advance on invalid opcode; registers untouched
# INIT_REG 1 99
# EXPECT_REG 1 99
# EXPECT_PC 0

.text
    .word 0
