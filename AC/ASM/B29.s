.data
    numero: .string "9000"
    numero2: .string "234"
    decena: .byte 0,10,20,30,40,50,60,70,80,90
    centena: .half 0,100,200,300,400,500,600,700,800,900
    milena: .half 0,1000,2000,3000,4000,5000,6000,7000,8000,9000
    
.text
    la a1 numero2
    
    jal atoi
    
    li a7 10
    ecall

#a1: str
strlen:
    li a0 0
    addi a2 a1 0
    lb a3 (0)a2
    beq a3 zero volver
    
loop:
    addi a0 a0 1
    addi a2 a2 1
    lb a3 (0)a2
    bne a3 zero loop

volver:
    ret


#a1: str
atoi:
    addi t5 ra 0
    jal strlen
    addi ra t5 0
    
    #Nro de digitos
    addi t5 a0 0
    
    li a0 0
    
    la t2 milena
    la t3 centena
    la t4 decena
    addi t0 a1 0
    
    #Nro de digitos para comp
    li t6 4
    
    blt t5 t6 calcularCentena
    
    #Milena
    lb t1 0(t0)
    addi t1 t1 -0x30
    slli t1 t1 1
    add t2 t2 t1
    lh t1 0(t2)
    add a0 a0 t1
    addi t0 t0 1
    
    calcularCentena:
    addi t6 t6 -1
    blt t5 t6 calcularDecena
    
    #Centena
    lb t1 0(t0)
    addi t1 t1 -0x30
    slli t1 t1 1
    add t3 t3 t1
    lh t1 0(t3)
    add a0 a0 t1
    addi t0 t0 1
    
    calcularDecena:
    addi t6 t6 -1
    blt t5 t6 calcularUnidad
        
    #Decena
    lb t1 0(t0)
    addi t1 t1 -0x30
    add t4 t4 t1
    lb t1 0(t4)
    add a0 a0 t1
    addi t0 t0 1
    
    calcularUnidad:
    lb t1 0(t0)
    addi t1 t1 -0x30
    add a0 a0 t1

    ret