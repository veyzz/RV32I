# Sum of integers from 1 to 10.
# Result:
#   x3 = 55

.text
    li x1, 1
    li x2, 10
    li x3, 0

loop:
    add x3, x3, x1
    addi x1, x1, 1
    ble x1, x2, loop

    .word 0
