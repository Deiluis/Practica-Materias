.data
    vector: .word 100,-10,20,1000,66500,1000000,-20,34,56
    finvec:

.text
    la a1 vector
    la a2 finvec
    
    jal buscaMax

    li a7 10
    ecall
    
#a1: vec, a2: finvec
buscaMax:
    addi t1 a1 0
    lw a0 (0)t1
    addi t1 t1 4
    bge t1 a2 volver
    
loop:
    lw t2 (0)t1
    
    bge a0 t2 seguir
    addi a0 t2 0
    
    seguir:
        
    addi t1 t1 4	
    blt t1 a2 loop

volver:
    ret