.text
    li s0 10
    
    jal prueba
    li a7 10
    ecall

prueba:
    #Reservo espacio para 3 variables + fp
    addi sp sp -16
    sw s0 12 sp
    addi s0 sp 16
    
    #Guardo A
    li t0 7
    sw t0 8 sp
    
    #Guardo B
    li t0 6502
    sw t0 4 sp
    
    #Guardo C
    li t0 3
    sw t0 0 sp
    
    #Devuelvo sp y fp a sus valores originales
    lw s0 12 sp
    addi sp sp 16

    ret 