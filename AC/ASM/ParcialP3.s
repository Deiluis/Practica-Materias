.text
    li t1 1 #Inicial
    li t5 100 #Limite
    li t6 0x3b #ASCII del ;
    li a7 11
    
    #Imprimir t0 y t1
    addi a0 zero 0x30
    ecall
    addi a0 t6 0
    ecall
    addi a0 t1 0x30
    ecall
    addi a0 t6 0
    ecall

    add t2 zero t1

    loop:
        
    addi a0 t2 0
    li a7 1
    ecall
        
    addi t0 t2 0
    add t2 t2 t1
    addi t1 t0 0
    
    bge t2 t5 noImprimir
    addi a0 t6 0
    li a7 11
    ecall
    
    noImprimir:
    blt t2 t5 loop
    
    li a7 10
    ecall