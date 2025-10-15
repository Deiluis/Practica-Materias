.data
    vector: .word 100,56,20,1000,66500,1000000,-20,34,-10
    #vector: .word -20,-10,20,34,56,100,1000,66500,1000000
    finvec:

.text
    la a3 vector
    la a4 finvec
    
    sub t4 a4 a3
    srai t4 t4 2
    
    mainloop:
        jal pushMax
        addi t4 t4 -1
        
        beq a0 zero terminar
        blt zero t4 mainloop
    
    terminar:
    
    li a7 10
    ecall

pushMax:
    addi t0 a3 0
    addi t1 a4 -4
    
    li a0 0
    
loop:
    lw t2 (0)t0
    lw t3 (4)t0
    
    blt t2 t3 seguir
    sw t2 (4)t0
    sw t3 (0)t0
    li a0 1 #hubo cambio
    
    seguir:
    addi t0 t0 4
    blt t0 t1 loop

volver:
    ret