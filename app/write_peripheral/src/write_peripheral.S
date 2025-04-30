.text
main:
    li t0, 0          		# valor a enviar (inicia em 0)
    li t1, 1000       		# limite
    j loop_peripheral
    ret

loop_peripheral:
    slti t2, t0, 1000
    beq t2, zero, end

    # --- Escreve dado no endereço real do periférico
    la t2, endperifwrite
    lw t2, 0(t2)
    sw t0, 0(t2)

    # --- Escreve também no registrador de simulação (Vivado)
    la t2, dataperifwrite
    sw t0, 0(t2)

    # Chama a sub-rotina para simular periférico (pode ser ignorada em uso real)
    jal perif

    j loop_leitura

loop_leitura:
    # Verifica sinal de pronto (enable)
    la t2, endperifenable
    lw t2, 0(t2)
    lw t3, 0(t2)
    beq t3, zero, loop_leitura

    # Lê o valor invertido do periférico
    la t2, endperifread
    lw t2, 0(t2)
    lw t3, 0(t2)

    # Em simulação, também lê valor de dataperifread
    la t4, dataperifread
    lw t3, 0(t4)  # sobrescreve com dado da memória simulado (caso esteja sendo usada)

    not t4, t0
    bne t3, t4, end  # se resposta não for correta, termina com erro

    addi t0, t0, 1  # próximo valor
    j loop_peripheral

end:
    li  t0, 0x80000000
    sw	zero, 0(t0)   # sinaliza fim da simulação (ambiente externo)
	j   end
	
# --- Simula comportamento do periférico (somente em simulação)
perif:
    la s0, dataperifwrite
    lw s0, 0(s0)
    not s0, s0

    la s1, dataperifread
    sw s0, 0(s1)

    la s2, dataperifenable
    li s3, 1
    sw s3, 0(s2)

    ret

.data
# Endereços reais mapeados na memória
endperifwrite: 		.word	0x80000003
endperifread:		.word	0x80000001
endperifenable: 	.word	0x80000002

# Espaço para simulação em memória (usado no Vivado)
.space 20
dataperifwrite: 	.word	0
dataperifread:		.word	0
dataperifenable: 	.word 	0
