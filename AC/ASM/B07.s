.text
    li t1 57
    li a0 33
    li a7 11

loop:
    add t2 zero a0
    li a0 91
    ecall
    add a0 t2 zero
    ecall
    li a0 93
    ecall
    add a0 t2 zero
    addi a0 a0 1
    bge t1 a0 loop
    
    

    