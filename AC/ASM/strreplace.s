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

    #addi a1 t3 0
    #addi a2 t0 0
    #jal ra strCpy
    
    #addi a1 t0 0
    #addi a2 t1 0
    #addi a3 t2 0    
    #jal ra strReplace

    addi a1 t0 0
    jal ra strReverse

    li a7 10
    ecall
    
#a1 str1, a2 str2
strCmp:
    recorrerStrCmp:
    lb a3 (0)a1
    lb a4 (0)a2

    beq s2 zero volverStrCmp
    beq a4 zero volverStrCmp

    addi a1 a1 1
    addi a2 a2 1

    sub a3 a3 a4
    
    beq a3 zero recorrerStrCmp

    volverStrCmp:
    addi a0 a3 0
    ret
    
#a1 dest, a2 orig
strCpy:
    recorrerStrCpy:
    lb a3 (0)a2
    sb a3 (0)a1
    
    addi a1 a1 1
    addi a2 a2 1
    
    bne a3 zero recorrerStrCpy

    #Copia tambien el fin de cadena
    sb a3 (0)a1
    ret
    
#a1 str
strLen: 
    li a2 0
    
    recorrerStrLen:
    lb a3 (0)a1
    addi a2 a2 1
    addi a1 a1 1
    
    bne a3 zero recorrerStrLen
    
    #Resta el que se conto por el \0
    addi a0 a2 -1
    ret

#a1 str, a2 expBusq, a3 expReem
strReplace:
    #Cantidad de coincidencias
    li a4 0
    
    # Guardo retorno a main
    addi a5 ra 0
    
    #Por la longitud de la funcion, tengo usar los registros s sin calling conventions
    addi a6 a1 0
    addi a1 a2 0
    addi s0 a2 0
    addi s3 a3 0
    
    jal ra strLen
    addi a7 a0 0
    
    addi a1 a6 0
    addi a2 s0 0
    addi a3 s3 0
    
    #Resiagno el retorno
    addi ra a5 0
    
    recorrerStrReplace:
        lb a5 (0)a1
        lb a6 (0)a2
    
        sub s1 a5 a6
    
        bne s1 zero desiguales
    
            addi a2 a2 1
    
            bne a4 zero noGuardarInicio
    
                #Guardo la direccion de inicio de coincidencia
                addi s2 a1 0
    
            noGuardarInicio:
            addi a4 a4 1
    
            bne a4 a7 noEncontrado
                
                reemplazar:
                
                    lb s1 (0)a3
                    
                    beq s1 zero desiguales #Por si expReem llega a \0
                    
                    sb s1 (0)s2
                
                    addi s2 s2 1
                    addi a3 a3 1
                
                    lb s4 (0)s2
                
                #bge a1 s2 reemplazar
                bne s4 zero reemplazar
    
        desiguales:
        li a4 0
        addi a2 s0 0
        addi a3 s3 0
    
        noEncontrado:

    addi a1 a1 1
    bne a5 zero recorrerStrReplace
    
    ret
    
#a1 str1
strReverse:
    #Posiciono un puntero al final
    addi a2 a1 0
    
    recorrerStrHastaFinal:
        lb a3 (0)a2
        addi a2 a2 1
        bne a3 zero recorrerStrHastaFinal
    
        addi a2 a2 -2
    
    #Direccion de mitad de cadena
    sub a3 a2 a1
    srai a3 a3 1
    add a3 a3 a1
    
    #Retornar si no se puede
    
    
    intercambiar:
        lb a4 (0)a1
        lb a5 (0)a2
        
        sb a4 (0)a2
        sb a5 (0)a1
        
        addi a1 a1 1
        addi a2 a2 -1
        
        bge a3 a1 intercambiar

    volverStrReverse:
        ret