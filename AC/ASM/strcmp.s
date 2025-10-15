.data
    orig: .string "Que feo perder con Riestra"
    expBusq: .string "Riestra"
    expReem: .string "Palmeiras"
    copia:
.text
    la t0 orig
    la t1 expBusq
    la t2 expReem
    la t3 copia
    
    addi s0 t0 0
    jal ra strReplace

    li a7 10
    ecall

#fin:
#beq zero zero fin

#s0 str1, s1 str2
strCmp:
    recorrerStrCmp:
    lb s2 (0)s0
    lb s3 (0)s1

    beq s2 zero volverStrCmp
    beq s3 zero volverStrCmp

    addi s0 s0 1
    addi s1 s1 1

    sub s2 s2 s3
    
    beq s2 zero recorrerStrCmp

    volverStrCmp:
    addi a0 s2 0
    ret
    
#s0 dest, s1 orig
strCpy:
    recorrerStrCpy:
    lb s2 (0)s0
    sb s2 (0)s1
    
    addi s0 s0 1
    addi s1 s1 1
    
    bne s2 zero recorrerStrCpy

    #Copia tambien el fin de cadena
    sb s2 (0)s1
    ret
    
#s0 str
strLen: 
    li s1 0
    
    recorrerStrLen:
    lb s2 (0)s0
    addi s1 s1 1
    addi s0 s0 1
    
    bne s2 zero recorrerStrLen
    
    #Resta el que se conto por el \0
    addi a0 s1 -1
    ret

#s0 str, s1 expBusq, s2 expReem
strReplace:
    #Cantidad de coincidencias
    li s3 0
    
    # Guardo retorno a main
    addi s5 ra 0
    
    addi s4 s0 0
    addi s0 s1 0
    jal ra strLen
    addi s6 a0 0
    
    addi s0 s4 0
    
    recorrerStrReplace:
        lb s4 (0)s0
        lb s7 (0)s1
    
        sub s8 s4 s7
    
        bne s8 zero desiguales
    
            bne s3 zero noGuardarInicio
    
                #Guardo la direccion de inicio de coincidencia
                addi s9 s0 0
    
            noGuardarInicio:
            addi s3 s3 1
    
            bne s3 s6 noEncontrado
                
                reemplazar:
                
                    lb s10 0(s9)
                    sb s10 0(s2)
                
                    addi s9 s9 1
                    addi s2 s2 1
                
                bge s0 s9 reemplazar
    
        desiguales:
        li s3 0
    
        noEncontrado:
    
    addi s1 s1 1
    addi s0 s0 1
    
    bne s4 zero recorrerStrReplace
    
    
    #Resiagno el retorno a main y vuelvo
    addi ra s5 0
    ret

    
