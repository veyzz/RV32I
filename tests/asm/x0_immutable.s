# Verifies x0 reads as 0 after both I-type and R-type writes.
# EXPECT_REG 0 0
# EXPECT_REG 1 0
# EXPECT_REG 3 0
# EXPECT_PC 0x80000014

.text
    addi x0, x0, 1
    addi x1, x0, 0
    li   x2, 5
    add  x0, x2, x2
    add  x3, x0, x0
    .word 0
