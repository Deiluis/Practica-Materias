.data
    vec: .word 100,1000,65536,65537,1000000,0
    finVar:
    sep: .string ";"
.text
    la a1 vec
    la a2 finVar
    
    sub a2 a2 a1
    srai a2 a2 2

    jal ra printVector

    li a7 10
    ecall

#a1: vec, a2: ce
printVector:
    
    addi a3 a2 0
    slli a3 a3 2
    add a3 a1 a3
    
    beq a1 a3 volver
    
    la a5 sep
    lb a5 (0)a5
    
loop:
    li a7 1
    lw a0 (0)a1
    ecall
    
    addi a1 a1 4
    
    beq a1 a3 noEscribirSep
    
    li a7 11
    addi a0 a5 0
    ecall
    
    noEscribirSep:
    
    blt a1 a3 loop

volver:
    ret