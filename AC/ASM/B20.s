.data
    texto: .string "Hola mundo!"
.text
    la a1 texto
    jal ra strlen
    
    li a7 10
    ecall

#a1: str
strlen:
    li a0 0
    addi a2 a1 0
    lb a3 (0)a2
    beq a3 zero volver
    
loop:
    addi a0 a0 1
    addi a2 a2 1
    lb a3 (0)a2
    bne a3 zero loop

volver:
    ret