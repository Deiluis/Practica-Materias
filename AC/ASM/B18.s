.data
    texto: .string "Hola mundo!"
.text
    la a1 texto
    
    jal ra printStr
    
    li a7 10
    ecall

#a1: str
printStr:
    
    li a7 11
    lb a0 (0)a1
    
    beq a0 zero volver
    
loop:
    ecall
    addi a1 a1 1
    lb a0 (0)a1
    bne a0 zero loop

volver:
    ret