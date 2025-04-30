.text
.global main

main:
    li t0, 1              # Valor inicial a ser enviado
    li t1, 1000           # Limite

# loop_peripheral:
#     # bgt t0, t1, end       # Se t0 > 1000, vai para o fim

#     # Escreve valor no periférico
#     li t2, 0x80000003     # Endereço de escrita do periférico
#     sw t0, 0(t2)

# wait_ready:
#     li t3, 0x80000002     # Endereço do bit de "dado pronto"
#     lw t4, 0(t3)
#     beq t4, zero, wait_ready   # Espera até o bit ser 1

#     # Lê valor invertido do periférico
#     li t5, 0x80000001     # Endereço de leitura do valor invertido
#     lw t6, 0(t5)

#     not t4, t0            # t4 = ~t0  (reutilizado)
#     bne t6, t4, end       # Se não bater com o invertido, termina (erro)

#     addi t0, t0, 1        # Próximo valor
#     j loop_peripheral

# end:
#     li  t0, 0x80000000    # Sinaliza fim da simulação
#     sw  zero, 0(t0)
#     j   end
