.section .init
.global _start

/* Duvidas
O tamanho dos bits serem 32, não precisamos delimitar isso aqui?

A gente não vai salvar na memória os dados devolvidos pelo periférico? nem os dados que enviamos?

falta mais alguma coisa no código? ele está correto?

como faço o test_bench agora com o código do processador e do periférico? já que o processador tem software e o periférico é só hardware



*/

_start:
    # Configure system status MPP=0, MPIE=0, MIE=0
	csrw	mstatus, zero

	# Mask interrupts
	csrw	mie, zero

	# Clear pending interrupts
	csrw	mip, zero

    # Set stack to top of data memory
	li		sp, MEM_SIZE

    jal main

.end:
    li  t0, 0x80000000
    sw	zero, 0(t0)     # End simulation
	j   .end

.section .text
main:
    li t0, 0          # valor a enviar
    li t1, 1000       # limite
    jal loop_peripheral

loop_peripheral:
    slt t2, t0, 1000
    beq t2, zero, end
    li t2, 0x80000003
    sw t0, 0(t2)
    jal loop_leitura

loop_leitura:
    li t2, 0x80000002
    lw t3, 0(t2)
    beq zero, t3, loop_leitura; # if zero == t3 loop_leitura
    li t2, 0x80000001
    lw t3, 0(t2)              

    not t5, t0                # espera ~t0
    bne t3, t5, end           # se resposta não for correta, fim com erro

    addi t0, t0, 1            # próximo valor
    jal loop_peripheral
