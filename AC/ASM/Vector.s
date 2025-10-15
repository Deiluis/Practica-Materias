.data
    vector: .word 5,73,6502,96,2,-1
    finVector: .word 0
    mayor: .word 0
    menor: .word 0
    promedio: .word 0

.text
    la x5, vector
    
    la x6, finVector
    addi x6, x6, -1
    
    lw x8, 0(x5)
    lw x9, 0(x5)
    addi x5, x5, 4

recorrer:
    lw x7, 0(x5)
    bge x7, x8, cmpMayor
    addi x8, x7, 0

cmpMayor:
    blt x7, x9, aumentar
    addi x9, x7, 0

aumentar:
    addi x5, x5, 4
    bge x6, x5, recorrer
 
    
    
    