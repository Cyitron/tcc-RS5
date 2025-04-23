.text
main:
    li t0, 0          		# valor a enviar
    li t1, 1000       		# limite
    j loop_peripheral
    ret

loop_peripheral:
    slti t2, t0, 1000
    beq t2, zero, end
    la t2, endperifwrite
    lw t2, 0(t2)
    # li t2, endperifwrite # escrita do periferico
    sw t0, 0(t2)
    jal perif
    j loop_leitura

loop_leitura:
    la t2, endperifenable
    lw t2, 0(t2)
    # li t2, endperifenable
    lw t3, 0(t2)
    beq t3, zero, loop_leitura # if zero == t3 loop_leitura
    la t2, endperifread
    lw t2, 0(t2)
    # li t2, endperifread
    lw t3, 0(t2)              

    not t4, t0                	# espera ~t0
    bne t3, t4, end           	# se resposta não for correta, fim com erro

    addi t0, t0, 1            	# próximo valor
    j loop_peripheral

end:
    li  t0, 0x80000000		
    sw	zero, 0(t0)     	# End simulation
	j   end
	
perif:
    la s0, endperifwrite
    lw s0, 0(s0)
    not s0, s0
    la s1, endperifread
    lw s1, 0(s1)
    sw s0, 0(s1)
    la s2, endperifenable
    lw s2, 0(s2)
    li s3, 1
    sw s3, 0(s2)
    ret
	
.data
endperifwrite: 		.word	0x80000003 # endereco usado no riscv para escrever no periferico 		    0x80000003
endperifread:		.word	0x80000001 # endereco usado no riscv para ler no periferico 			    0x80000001
endperifenable: 	.word	0x80000002 # endero usado no riscv para sinalizar dado pronto pra leitura 	0x80000002

.space 20
dataperifwrite: 	.word	0
dataperifread:		.word	0
dataperifenable: 	.word 	0

