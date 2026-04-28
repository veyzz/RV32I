# INIT_REG 1 0xffffffff
# INIT_REG 2 1
# EXPECT_REG 3 0
# EXPECT_PC 8

.text
    bgeu x1, x2, target
    addi x3, x0, 99
target:
    .word 0
