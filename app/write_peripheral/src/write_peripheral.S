        .text
main:
        li   t0, 1               # valor a enviar (começa em 1)
        li   t1, 100            # limite (1000 iterações)
        j    loop_peripheral

loop_peripheral:
        # Se t0 > 1000, termina
        bgt  t0, t1, end

        # Escreve t0 no periférico
        la   t2, endperifwrite
        lw   t2, 0(t2)           # t2 = 0x80000003
        sw   t0, 0(t2)

        # Aguarda flag de dado pronto = 1
loop_poll:
        la   t2, endperifenable
        lw   t2, 0(t2)           # t2 = 0x80000002
        lw   t3, 0(t2)           # t3 = *0x80000002*
        beq  t3, zero, loop_poll # se 0, continua aguardando

        # Lê o dado invertido
        la   t2, endperifread
        lw   t2, 0(t2)           # t2 = 0x80000001
        lw   t3, 0(t2)           # t3 = *0x80000001*

        # Verifica se t3 == ~t0
        not  t4, t0
        bne  t3, t4, end         # se incorreto, sai com erro

        # Prepara próxima iteração
        addi t0, t0, 1
        j    loop_peripheral

end:
        # Sinaliza fim de simulação
        li   t0, 0x80000000
        sw   zero, 0(t0)
        j    end

perif:
        # Rotina que o “periférico” executa:
        # lê valor em dataperifwrite, inverte, armazena em dataperifread e
        # seta flag em dataperifenable
        la   s0, dataperifwrite
        lw   s0, 0(s0)
        not  s0, s0

        la   s1, endperifread
        lw   s1, 0(s1)
        sw   s0, 0(s1)

        la   s2, endperifenable
        lw   s2, 0(s2)
        li   s3, 1
        sw   s3, 0(s2)

        ret

        .data
endperifwrite:   .word 0x80000003   # endereço de escrita do periférico
endperifread:    .word 0x80000001   # endereço de leitura (inverso)
endperifenable:  .word 0x80000002   # endereço da flag “data_ready”

        .space 20
dataperifwrite:  .word 0
dataperifread:   .word 0
dataperifenable: .word 0
