# INIT_REG 1 1
# INIT_REG 2 0xffffffff
# EXPECT_REG 3 0
# EXPECT_PC 8

.text
    bltu x1, x2, target
    addi x3, x0, 99
target:
    .word 0
