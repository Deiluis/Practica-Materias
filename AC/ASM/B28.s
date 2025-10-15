.data
    numero: .string "9000"
    numero2: .string "0065"
    decena: .byte 0,10,20,30,40,50,60,70,80,90
    centena: .half 0,100,200,300,400,500,600,700,800,900
    milena: .half 0,1000,2000,3000,4000,5000,6000,7000,8000,9000
    
.text
    la a1 numero
    
    jal atoi4
    
    li a7 10
    ecall


#a1: str
atoi4:
    li a0 0
    la t2 milena
    la t3 centena
    la t4 decena
    addi t0 a1 0
    
    #Milena
    lb t1 0(t0)
    addi t1 t1 -0x30
    slli t1 t1 1
    add t2 t2 t1
    lh t1 0(t2)
    add a0 a0 t1
    addi t0 t0 1
    
    #Centena
    lb t1 0(t0)
    addi t1 t1 -0x30
    slli t1 t1 1
    add t3 t3 t1
    lh t1 0(t3)
    add a0 a0 t1
    addi t0 t0 1
    
    #Decena
    lb t1 0(t0)
    addi t1 t1 -0x30
    add t4 t4 t1
    lb t1 0(t4)
    add a0 a0 t1
    addi t0 t0 1
    
    #Unidad
    lb t1 0(t0)
    addi t1 t1 -0x30
    add a0 a0 t1
    
    ret