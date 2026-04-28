# INIT_REG 1 5
# INIT_REG 2 5
# EXPECT_REG 3 0
# EXPECT_PC 8

.text
    beq x1, x2, target
    addi x3, x0, 99
target:
    .word 0
