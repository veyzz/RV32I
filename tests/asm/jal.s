# EXPECT_REG 1 4
# EXPECT_REG 3 0
# EXPECT_PC 8

.text
    jal x1, target
    addi x3, x0, 99
target:
    .word 0
