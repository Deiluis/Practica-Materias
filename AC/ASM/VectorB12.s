.data
    vector: .string "Que feo perder con Riestra"
    
.text
    la t0 vector
    li a7 11

recorrerStr:
    lb a0 (0)t0
    addi t0 t0 1
    ecall
    #bne t0 zero recorrerStr
    