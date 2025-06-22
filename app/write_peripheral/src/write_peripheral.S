.section .init
.global _start
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
	li	s10, 0x80000000		# this will interrupt the simulation (assertion)
	sw	zero, 0(s10)
	jal zero, .end

.text
main:
    li s0, 1              # Valor inicial a ser enviado
    li t1, 1000           # Limite

loop_peripheral:
    bgt s0, t1, end       # Se s0 > 1000, vai para o fim

    # Escreve valor no periférico
    la t2, dataread       # Carrega endereço da palavra
    lw t2, 0(t2)          # t2 = 0x8000000c
    sw s0, 0(t2)

wait_ready:
    la t3, dataenable     # Endereço do bit "data ready"
    lw t3, 0(t3)          # t3 = 0x80000008
    lw t4, 0(t3)          # lê valor nesse endereço
    beq t4, zero, wait_ready   # Espera até bit ser 1

    # Lê valor invertido do periférico
    la t5, datainverse
    lw t5, 0(t5)          # t5 = 0x80000004
    lw t6, 0(t5)          # t6 = valor invertido lido

    not t4, s0            # t4 = ~s0
    bne t6, t4, end       # Se não bater com o invertido, termina (erro)

    addi s0, s0, 1        # Próximo valor
    j loop_peripheral

end:
    jr  ra

.data
dataread:     .word   0x8000000c
dataenable:   .word   0x80000008
datainverse:  .word   0x80000004