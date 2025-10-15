.text
    li a0 12
    
    jal div8
    
    li a7 10
    ecall
    
div8:
    addi t0 a0 0
    
    bge a0 zero desp
    neg t0 t0
    
    desp:
    srai t0 t0 3
    
    bge a0 zero volver
    neg t0 t0
    
volver:
    ret