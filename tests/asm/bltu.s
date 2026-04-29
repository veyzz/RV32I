# EXPECT_REG 3 0
# EXPECT_PC 0x80000010

.text
    li x1, 1
    li x2, 0xffffffff
    bltu x1, x2, target
    addi x3, x0, 99
target:
    .word 0
