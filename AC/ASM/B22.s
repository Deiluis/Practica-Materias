.data
    cad1: .string "Hola mundo!"
    cad2: .string "Otra cadena de texto"
    cad3: .string "Hola mundo!"
    cad4: .string "Hola mundo! mas largo"
    
.text
    la a1 cad1
    la a2 cad2
    
    jal ra strcmp
    
    li a7 10
    ecall

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