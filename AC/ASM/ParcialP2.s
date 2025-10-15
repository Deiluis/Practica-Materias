.data
    vector: .half -10, -20, 10, -5
    
.text
    li a7 1
    la a0 vector
    
    jal promedio
    ecall
    
    li a7 10
    ecall
    
promedio:
    #Cant elem
    li t0 4
    addi t1 a0 0
    li a0 0
    
    loop:
    lh t2 0 t1
    add a0 a0 t2
    addi t1 t1 2
    addi t0 t0 -1
    bne t0 zero loop
    
    #Guardo sumatoria inicial
    addi t3 a0 0
    
    bge a0 zero sumatoriaInicialPos
    neg a0 a0
    
    sumatoriaInicialPos:    
    srai a0 a0 2
    
    bge t3 zero volver
    neg a0 a0
    
    volver:
    ret