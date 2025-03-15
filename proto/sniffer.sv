/* sniffer.sv
top archive: RS5_FPGA_Platform.sv

top archive of sniffer_dp.sv and sniffer_fsm.sv
*/

module sniffer(
    input  logic            clk,
    input  logic            reset_n,
    input  logic            enable_i,
    input  logic [3:0]      write_enable_i,
    input  logic [31:0]     data_address_i,
    input  logic [31:0]     data_i,
    output logic [31:0]     data_o
);  

    logic w_ena_1;
    logic w_ena_2;

    sniffer_dp sniffer_dp(
        .clk            (clk),
        .reset_n        (reset_n),
        .data_i         (data_i),
        .data_o         (data_o),
        .ena_1          (w_ena_1),
        .ena_2          (w_ena_2)

    );

    sniffer_fsm sniffer_fsm(
        .clk            (clk),
        .reset_n        (reset_n),
        .ena_1          (w_ena_1),
        .ena_2          (w_ena_2),
        .data_address_i (data_address_i),
        .enable_i       (enable_i)
    );

endmodule