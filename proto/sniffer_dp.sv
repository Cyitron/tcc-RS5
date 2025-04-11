module sniffer_dp (
    input  logic            clk,
    input  logic            reset_n,
    input  logic [31:0]     data_i,
    output logic [31:0]     data_o,
    input  logic            get_data_ce,  // Captura do dado do processador
    input  logic            gen_data_ce,  // Gera o dado invertido
    input  logic            new_data_ce,  // (Pode ser usado para atualizar flip-flops internos, se necessário)
    input  logic            av_data,      // Indica que o dado está pronto para ser lido
    input  logic            seletor_hab
);

    // Registradores internos
    logic [31:0] data_cpu_in;   // Armazena o dado capturado
    logic [31:0] new_data;      // Armazena o dado invertido
    logic [31:0] data_ready;    // sinaliza que o dado está pronto

    // Captura do dado quando get_data_ce estiver ativo
    always_ff @(posedge clk, negedge reset_n) begin
        if (reset_n == 0)
            data_cpu_in <= 32'b0;
        else if (get_data_ce)
            data_cpu_in <= data_i;
        // Caso contrário, mantém o valor
    end

    // Geração do dado invertido quando gen_data_ce estiver ativo
    always_ff @(posedge clk, negedge reset_n) begin
        if (reset_n == 0)
            new_data <= 32'b0;
        else 
        if (gen_data_ce)
            new_data <= ~data_cpu_in;
        // Caso contrário, mantém o valor
    end

    // flip-flop data_avaiable
    always_ff @(posedge clk, negedge reset_n) begin
        if (reset_n == 0)
            data_ready <= 32'b0;
        else if (new_data_ce)
            if (av_data)
                data_ready <= 32'h00000001;
            else
                data_ready <= 32'b0;
    end

    // Multiplexador para selecionar a saída
    // Se av_data estiver ativo, envia o dado invertido; caso contrário, envia uma sequência padrão (aqui 32'b0).
    always_comb begin
        data_o = 32'h0; // valor default (importante)
        if (seletor_hab)
            data_o = data_ready;
        else
        data_o = new_data;
    end

endmodule