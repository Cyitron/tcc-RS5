module sniffer_dp (
    input  logic            clk,
    input  logic            reset_n,
    input  logic [31:0]     data_i,
    output logic [31:0]     data_o,
    input  logic            get_data_ce,  // Captura do dado do processador
    input  logic            gen_data_ce,  // Gera o dado invertido
    input  logic            new_data_ce,  // (Pode ser usado para atualizar flip-flops internos, se necessário)
    input  logic            av_data       // Indica que o dado está pronto para ser lido
);

    // Registradores internos
    logic [31:0] data_snf_1; // Armazena o dado capturado
    logic [31:0] data_snf_2; // Armazena o dado invertido

    // Captura do dado quando get_data_ce estiver ativo
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            data_snf_1 <= 32'b0;
        else if (get_data_ce)
            data_snf_1 <= data_i;
        // Caso contrário, mantém o valor
    end

    // Geração do dado invertido quando gen_data_ce estiver ativo
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            data_snf_2 <= 32'b0;
        else if (gen_data_ce)
            data_snf_2 <= ~data_snf_1;
        // Caso contrário, mantém o valor
    end

    // Multiplexador para selecionar a saída
    // Se av_data estiver ativo, envia o dado invertido; caso contrário, envia uma sequência padrão (aqui 32'b0).
    assign data_o = (av_data) ? data_snf_2 : 32'b0;

endmodule