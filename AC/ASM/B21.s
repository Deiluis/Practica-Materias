.data
    texto: .string "YVAN EHT NIOJ"
.text
    la a1 texto
    jal ra strReverse
    jal ra printStr
    
    li a7 10
    ecall


#a1: str
strReverse:
    addi a7 ra 0
    jal ra strlen
    addi ra a7 0
    
    beq a0 zero volverStrReverse
    
    #Puntero a str
    addi a2 a1 0
    
    #Puntero al final
    add a3 a1 a0
    addi a3 a3 -1

loopStrReverse:

    lb a0 (0)a2
    lb a5 (0)a3
    
    sb a0 (0)a3
    sb a5 (0)a2
    
    addi a2 a2 1
    addi a3 a3 -1
 
    bge a3 a2 loopStrReverse
    
volverStrReverse:
    ret


#a1: str
strlen:
    li a0 0
    addi a2 a1 0
    lb a3 (0)a2
    beq a3 zero volverStrLen
    
loopStrLen:
    addi a0 a0 1
    addi a2 a2 1
    lb a3 (0)a2
    bne a3 zero loopStrLen

volverStrLen:
    ret
    

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