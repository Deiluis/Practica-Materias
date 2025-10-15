.data
    frase: .string "Esto es una frase de prueba"
    exp: .string "una"
    exp2: .string "no"
    
.text
    la a1 frase
    la a2 exp
    jal ra strcontains
    
    la a2 exp2
    jal ra strcontains
    
    li a7 10
    ecall

#a1: str, a2: exp
strcontains:
    addi s1 a1 0
    addi s11 ra 0
    
loopStrcontains:
    jal strcmp
    
    beq a0 zero encontrado
    
    lb s2 (0)a1
    addi a1 a1 1
     
    bne s2 zero loopStrcontains
    
    #Para verificar que no se encuentre tampoco cuando la
    #dif de a1 al fin de cadena es menor al tamaño de a2
    #fijarse ese caso
    
noEncontrado:
    li a0 0
    beq zero zero volverStrcontains

encontrado:
    addi a0 a0 1
    
volverStrcontains:
    addi a1 s1 0
    addi ra s11 0
    ret
    
    
    
#a1: str 1, a2: str2
strcmp:
    addi a3 a1 0
    addi a4 a2 0
    
loopStrcmp:
    
    lb a5 (0)a3
    lb a6 (0)a4
    
    #Si no tengo en cuenta los largos, descomento esto
    beq a5 zero volverStrcmp
    beq a6 zero volverStrcmp
    
    sub a0 a5 a6
    
    addi a3 a3 1
    addi a4 a4 1
    
    #Si tengo en cuenta los largos, descomento esto
    #beq a5 zero volverStrcmp
    #beq a6 zero volverStrcmp
    
    beq a0 zero loopStrcmp
    
volverStrcmp:
    ret