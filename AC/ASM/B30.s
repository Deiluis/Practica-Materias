.text
    li a1 3
    li a2 5
    
    jal mult
    
    li a7 10
    ecall
    
mult:
    li a0 0
    addi t0 a2 0
    
loop:
    blt t0 zero t0neg
    
    addi t0 t0 -1
    add a0 a0 a1
    beq zero zero seguir
    
    t0neg:
    addi t0 t0 +1
    sub a0 a0 a1
        
    seguir:
    bne t0 zero loop
    
    ret