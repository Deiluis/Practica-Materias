.data
    numero: .string "123"
    numero2: .string "065"
    decena: .byte 0,10,20,30,40,50,60,70,80,90
    centena: .half 0,100,200,300,400,500,600,700,800,900
    
.text
    la a1 numero2
    
    jal atoi3
    
    li a7 10
    ecall


#a1: str
atoi3:
    li a0 0
    la t2 centena
    la t3 decena
    addi t0 a1 0
    
    #Centena
    lb t1 0(t0)
    addi t1 t1 -0x30
    slli t1 t1 1
    add t2 t2 t1
    lh t1 0(t2)
    add a0 a0 t1
    addi t0 t0 1
    
    #Decena
    lb t1 0(t0)
    addi t1 t1 -0x30
    add t3 t3 t1
    lb t1 0(t3)
    add a0 a0 t1
    addi t0 t0 1
    
    #Unidad
    lb t1 0(t0)
    addi t1 t1 -0x30
    add a0 a0 t1
    
    ret