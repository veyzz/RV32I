# EXPECT_REG 3 1

.text
    li x1, 1
    li x2, 0xffffffff
    sltu x3, x1, x2
    .word 0
