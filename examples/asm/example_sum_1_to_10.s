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

    # Output buffer at 0x80000100: "sum = " + number + "\n"
    lui t4, 0x80000
    addi t4, t4, 0x100

    li t5, 's'
    sb t5, 0(t4)
    li t5, 'u'
    sb t5, 1(t4)
    li t5, 'm'
    sb t5, 2(t4)
    li t5, ' '
    sb t5, 3(t4)
    li t5, '='
    sb t5, 4(t4)
    li t5, ' '
    sb t5, 5(t4)

    # Convert x3 to decimal without DIV/REM.
    add t0, x3, x0
    li t1, 0
    bge t0, x0, abs_done
    li t1, 1
    sub t0, x0, t0
abs_done:

    addi t5, t4, 40
    add t2, t5, x0
    bne t0, x0, digits_loop_entry
    addi t2, t2, -1
    li t3, '0'
    sb t3, 0(t2)
    beq x0, x0, digits_done

digits_loop_entry:
    li t3, 0
    add t6, t0, x0
div10_loop:
    li a6, 10
    blt t6, a6, div10_done
    addi t3, t3, 1
    addi t6, t6, -10
    beq x0, x0, div10_loop
div10_done:
    addi t6, t6, '0'
    addi t2, t2, -1
    sb t6, 0(t2)
    add t0, t3, x0
    bne t0, x0, digits_loop_entry
digits_done:

    beq t1, x0, sign_done
    addi t2, t2, -1
    li t3, '-'
    sb t3, 0(t2)
sign_done:

    addi t6, t4, 6
copy_digits:
    bgeu t2, t5, copy_done
    lb a6, 0(t2)
    sb a6, 0(t6)
    addi t2, t2, 1
    addi t6, t6, 1
    beq x0, x0, copy_digits
copy_done:

    li a6, '\n'
    sb a6, 0(t6)
    sub a2, t6, t4
    addi a2, a2, 1

    # write(1, buf, len)
    li a0, 1
    add a1, t4, x0
    li a7, 64
    ecall

    # exit(0)
    li a0, 0
    li a7, 93
    ecall
