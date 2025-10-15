.data
    cad1: .string "Hola mundo!"
    cad2: .string "HOLA MUNDO!"
    
.text
    la a1 cad1
    la a2 cad2
    
    jal ra strcmpi
    
    li a7 10
    ecall

#a1: str1, a2: str2
strcmpi:
    addi a3 a1 0
    addi a4 a2 0
    
    addi a7 ra 0
    addi s1 a1 0
    
loopStrcmpi:
    
    lb a5 (0)a3
    lb a6 (0)a4
    
    #Si no tengo en cuenta los largos, descomento esto
    beq a5 zero volverStrcmpi
    beq a6 zero volverStrcmpi
    
    addi a1 a5 0
    jal ra toLower
    addi a5 a0 0
    
    addi a1 a6 0
    jal ra toLower
    addi a6 a0 0
    
    sub a0 a5 a6
    
    addi a3 a3 1
    addi a4 a4 1
    
    #Si tengo en cuenta los largos, descomento esto
    #beq a5 zero volverStrcmpi
    #beq a6 zero volverStrcmpi
    
    beq a0 zero loopStrcmpi
    
volverStrcmpi:
    addi ra a7 0
    addi a1 s1 0
    ret
    
    
#a1: c
toLower:
    addi a0 a1 0
    
    li t0 0x41 #A
    blt a1 t0 volverToLower
    li t0 123 #z+1
    bge a1 t0 volverToLower
    
    ori a0 a0 0x20
    
volverToLower:
    ret
    