.data
    pal: .string "HoLa MUNdo!"
    pal2: .string "Hola2"
.text    
    la a2 pal
    
loop:
    lb a1 (0)a2
    jal ra toLower
    sb a0 (0)a2
    
    addi a2 a2 1
        
    bne a1 zero loop
    
    li a7 10
    ecall
    
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
    
#a1: c
toUpper:
    addi a0 a1 0
    
    li t0 0x41 #A
    blt a1 t0 volverToUpper
    li t0 123 #z+1
    bge a1 t0 volverToUpper
    
    andi a0 a0 0xdf
    
volverToUpper:
    ret
    

    