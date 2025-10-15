.data
    vector: .word 100,-10,20,1000,66500,1000000,-20,34,56
    finvec:

.text
    la a3 vector
    
    addi a3 a3 4
    addi a4 a3 12
    
    jal swap
    
    li a7 10
    ecall
    
swap:
    lw t0 (0)a3
    lw t1 (0)a4
    sw t0 (0)a4
    sw t1 (0)a3
    ret