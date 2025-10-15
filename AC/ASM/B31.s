.text
    li a1 8
    li a2 0
    
    jal divide
    
    li a7 10
    ecall

#a1: dividendo, a2: divisor
divide:
    li a0 -1
    beq a2 zero volver
    li a0 0
    beq a1 zero volver
    
    evaluarDividendo:
    bge a1 zero dividendoPositivo
    neg t1 a1
    beq zero zero evaluarDivisor
    
    dividendoPositivo:
    addi t1 a1 0
        
    evaluarDivisor:
    bge a2 zero divisorPositivo
    neg t2 a2
    beq zero zero loop
    
    divisorPositivo:
    addi t2 a2 0

loop: 
    sub t1 t1 t2
    addi a0 a0 1
    bge t1 t2 loop

    bge a1 zero evaluarDivisorRes
    neg a0 a0

    evaluarDivisorRes:
    bge a2 zero volver
    neg a0 a0

volver:
    ret 