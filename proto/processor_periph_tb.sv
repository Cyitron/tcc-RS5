// TESTBENCH PERIFERICO E PROCESSADOR JUNTOS

`include "../rtl/RS5_pkg.sv"

`timescale 1ns/1ps

module processor_peripheral
    import RS5_pkg::*;
(

);
    localparam int              i_cnt = 2;
    logic                       clk, reset_n;

    RS5_FPGA_Platform #(
        .i_cnt      (i_cnt),
        .CLKS_PER_BIT_UART(5)
    ) dut (
        .clk        (clk), 
        .reset_n    (reset_n)
    );

    

    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    initial begin
    reset_n = 0;
    #20;
    reset_n = 1;
    end

//    always_ff @(posedge clk) begin
//        if ((write_enable_i != 0) && (enable_peripherals == 1) && (cpu_data_address == 32'h80000003)) // Simply checks if A equals B
//        assert (cpu_data_address != 1000) $display ("O contador chegou a 1000");
//    end
endmodule