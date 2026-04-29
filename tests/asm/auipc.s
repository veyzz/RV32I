# auipc adds (imm << 12) to current PC; here PC = 0x80000000
# EXPECT_REG 1 0x92345000

.text
    auipc x1, 0x12345
    ebreak
