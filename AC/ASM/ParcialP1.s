.data
    texto: .string "Texto de Prueba1"

.text
    li a7 4
    la a0 texto
    
    jal normalizar
    ecall
    
    li a7 10
    ecall


normalizar:
    addi t2 a0 0
    addi t3 a0 0
    addi t4 ra 0
    
    beq zero zero verificar
    
    loop:
    jal aMay
    sb a0 0 t3
    addi t3 t3 1
    
    verificar:
    lb a0 0 t3
    bne a0 zero loop
    
    addi a0 t2 0
    addi ra t4 0
    ret

#a0: c
aMay:
    li t0 0x41
    li t1 0x7b #z+1
    
    blt a0 t0 volverAMay
    bge a0 t1 volverAMay
    
    andi a0 a0 0xdf
    
volverAMay:
    ret
    