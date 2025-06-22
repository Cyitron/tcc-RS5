module sniffer_fsm (
    input  logic            clk,
    input  logic            reset_n,
    output logic            get_data_ce,  // Sinal para o datapath capturar o dado do processador
    output logic            gen_data_ce,  // Sinal para o datapath gerar o dado invertido
    output logic            new_data_ce,  // Sinal que indica que chegou um novo dado
    output logic            av_data,      // Sinal para avisar que o dado está pronto para leitura
    output logic            seletor_hab,  // habilita o seletor
    input  logic [3:0]      write_enable_i,
    input  logic [31:0]     data_address_i,
    input  logic            enable_i
);

  // Definindo os estados da FSM com um tipo enumerado
  typedef enum logic [1:0] {
      S0_GET_DATA,  // Estado de captura de dado
      S1_GEN_DATA,  // Estado de geração do dado invertido e sinalização de novo dado
      S2_WAIT_READ, // Estado de espera pela leitura do processador
      S3_RESET      // Estado que reseta a sinalização de dado pronto
  } state_t;

  state_t state = S0_GET_DATA, next_state;

  // Bloco combinacional para calcular o próximo estado e gerar as saídas
  always_comb begin
    // Valores default dos sinais de controle
    get_data_ce = 0;
    gen_data_ce = 0;
    new_data_ce = 0;
    av_data     = 0;
    seletor_hab = 0;
    next_state  = state; // Por padrão, mantém o estado atual

    case (state)
      S0_GET_DATA: begin
        // Sempre captura o dado do processador
        get_data_ce = 1;
        // Se a operação for direcionada ao sniffer, avança para S1
        if ((data_address_i[31:28] >= 4'h8) &&
            (enable_i == 1) &&
            (write_enable_i != 4'b0000))
          next_state = S1_GEN_DATA;
        else
          next_state = S0_GET_DATA;
      end

      S1_GEN_DATA: begin
        // Sinaliza para gerar o dado invertido e avisa que há novo dado
        gen_data_ce = 1;
        new_data_ce = 1;
        av_data     = 1;
        // Após gerar o dado, vai para o estado de espera pela leitura
        next_state = S2_WAIT_READ;
      end

      S2_WAIT_READ: begin
        // Enquanto o processador não confirmar a leitura, permanece em S2.
        // Aqui, assumimos que o processador sinaliza a leitura concluída
        // mudando o endereço para 32'h80000004 (ou outra condição definida).
        if ((data_address_i == 32'h80000004) &&
            (write_enable_i == 4'b0000) &&
            (enable_i == 1)
            ) begin
            seletor_hab = 0;
            next_state = S3_RESET;
        end
        else if ((data_address_i == 32'h80000008) &&
            (write_enable_i == 4'b0000) &&
            (enable_i == 1)
            ) begin// endereço que tem o bit de new_data_ce para o processador ler no endereço 32'h80000008
            seletor_hab = 1;
            next_state = S2_WAIT_READ;
        end
        else
            next_state = S2_WAIT_READ;
      end

      S3_RESET: begin
        // Reseta a indicação de dado pronto para leitura
        av_data = 0;
        // Pode-se manter new_data_ce ativo se necessário ou desativá-lo, conforme a implementação do datapath
        new_data_ce = 1; // ou 0, dependendo da lógica desejada
        // Retorna para S0 para capturar nova operação
        next_state = S0_GET_DATA;
      end

      default: begin
        next_state = S0_GET_DATA;
      end
    endcase
  end

    always_ff @(posedge clk) begin
        if (reset_n == 0)
            state <= S0_GET_DATA;
        else
            state <= next_state;
    end

endmodule