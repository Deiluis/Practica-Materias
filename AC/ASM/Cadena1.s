.data
    vector: .string "Que feo perder con Riestra"
    copiaVec:
.text
    la t0 vector
    li a7 11
    li t2 0x20
    
recorrerStr:
    lb t1 (0)t0
    addi t0 t0 1
    addi a0 t1 0
    
    beq a0 t2 ignorarEspacio
    andi a0 a0 0xdf
    
ignorarEspacio:
    ecall
    bne t1 zero recorrerStr

