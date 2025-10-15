.data
    vec: .word 100,1000,65536,65537,1000000,0

.text
    la t0 vec
    lw t1 (0)t0
    
    # Inicializar en 0
    addi t2 zero 0
    
    beq t1 zero fin
    
loop:
    addi t2 t2 1
    addi t0 t0 4
    lw t1 (0)t0
    
    bne t1 zero loop
    
fin:
    addi a7 zero 10
    ecall