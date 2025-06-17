module sniffer_v(
    clk,
    reset_n,
    enable_i,
    write_enable_i,
    data_address_i,
    data_i,
    data_o
);

    input  wire            clk;
    input  wire            reset_n;
    input  wire            enable_i;
    input  wire [3:0]      write_enable_i;
    input  wire [31:0]     data_address_i;
    input  wire [31:0]     data_i;
    output wire [31:0]     data_o;

    assign data_o = (enable_i == 1'b1) ? 1'b1 : 1'b0;


endmodule