module sniffer(
    input  logic            clk,
    input  logic            reset_n,
    input  logic            enable_i,
    input  logic [3:0]      write_enable_i,
    input  logic [31:0]     data_address_i,
    input  logic [31:0]     data_i,
    output logic [31:0]     data_o
);

    // Sinais de controle gerados pela FSM
    logic get_data_ce;
    logic gen_data_ce;
    logic new_data_ce;
    logic av_data;

    // Instanciação do datapath
    sniffer_dp sniffer_dp_inst (
        .clk            (clk),
        .reset_n        (reset_n),
        .data_i         (data_i),
        .data_o         (data_o),
        .get_data_ce    (get_data_ce),
        .gen_data_ce    (gen_data_ce),
        .new_data_ce    (new_data_ce),
        .av_data        (av_data),
        .seletor_hab    (seletor_hab)
    );

    // Instanciação da FSM
    sniffer_fsm sniffer_fsm_inst (
        .clk            (clk),
        .reset_n        (reset_n),
        .data_address_i (data_address_i),
        .enable_i       (enable_i),
        .write_enable_i (write_enable_i),
        .get_data_ce    (get_data_ce),
        .gen_data_ce    (gen_data_ce),
        .new_data_ce    (new_data_ce),
        .av_data        (av_data),
        .seletor_hab    (seletor_hab)
    );

endmodule
