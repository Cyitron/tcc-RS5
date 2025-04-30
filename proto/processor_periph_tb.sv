// TESTBENCH PERIFERICO E PROCESSADOR JUNTOS

`include "../rtl/RS5_pkg.sv"

`timescale 1ns/1ps

module processor_peripheral
    import RS5_pkg::*;
#(
    parameter int           i_cnt       = 2,
    parameter environment_e Environment = FPGA,
    parameter mul_e         MULEXT      = MUL_M,
    parameter atomic_e      AMOEXT      = AMO_A,
    parameter bit           COMPRESSED  = 1'b1,
    parameter bit           XOSVMEnable = 1'b0,
    parameter bit           ZIHPMEnable = 1'b0,
    parameter bit           ZKNEEnable  = 1'b0,
    parameter bit           VEnable     = 1'b0,
    parameter bit           BRANCHPRED  = 1'b1,
    parameter int           VLEN        = 64

);
    logic                       clk, reset_n;
    logic enable_i;
    logic [31:0]            cpu_instruction_address, cpu_instruction;
    logic [31:0]            cpu_data_address, cpu_data_in, cpu_data_out;
    logic                   cpu_operation_enable, enable_ram, enable_peripherals, enable_rtc, enable_plic;
    logic                   enable_rtc_r, enable_plic_r, enable_peripherals_r;
    logic [63:0]            mtime;
    logic [31:0]            data_bram;
    logic [63:0]            data_rtc;
    logic [32:0]            data_plic;
    logic [31:0]            data_peripherals;
    logic [3:0]             cpu_write_enable;
    logic                   stall;
    logic                   mei, mti;
    logic                   interrupt_ack;
    logic [31:0]            irq;
    logic [i_cnt:1]         irq_peripherals, iack_peripherals;

    assign irq = {20'h0, mei, 3'h0, mti, 7'h0};
    
    always_comb begin
        if (cpu_operation_enable) begin
            if (cpu_data_address[31:28] < 4'h2) begin // primeiros 512MB
                enable_ram          = 1'b1;
                enable_rtc          = 1'b0;
                enable_plic         = 1'b0;
                enable_peripherals  = 1'b0;
            end
            else if (cpu_data_address[31:28] < 4'h3) begin // 512MB
                enable_ram          = 1'b0;
                enable_rtc          = 1'b1;
                enable_plic         = 1'b0;
                enable_peripherals  = 1'b0;
            end
            else if (cpu_data_address[31:28] < 4'h8) begin // 1GB
                enable_ram          = 1'b0;
                enable_rtc          = 1'b0;
                enable_plic         = 1'b1;
                enable_peripherals  = 1'b0;
            end
            else /*if (cpu_data_address[31:28] >= 4'h8)*/ begin // 2GB 
                enable_ram          = 1'b0;
                enable_rtc          = 1'b0;
                enable_plic         = 1'b0;
                enable_peripherals  = 1'b1;
            end
        end
        else begin
            enable_ram          = 1'b0;
            enable_rtc          = 1'b0;
            enable_plic         = 1'b0;
            enable_peripherals  = 1'b0;
        end
    end

    always_ff @(posedge clk) begin
        enable_rtc_r            <= enable_rtc;
        enable_plic_r           <= enable_plic;
        enable_peripherals_r    <= enable_peripherals;
    end

    always_comb begin
        if (enable_rtc_r) begin
            cpu_data_in = data_rtc[31:0];
        end
        else if (enable_plic_r) begin
            cpu_data_in = data_plic[31:0];
        end
        else if (enable_peripherals_r) begin
            cpu_data_in = data_peripherals;
        end
        else begin
            cpu_data_in = data_bram;
        end
    end
    
    RS5 #(
        .Environment    (Environment),
        .MULEXT         (MULEXT),
        .AMOEXT         (AMOEXT),
        .XOSVMEnable    (XOSVMEnable),
        .ZIHPMEnable    (ZIHPMEnable),
        .ZKNEEnable     (ZKNEEnable),
        .COMPRESSED     (COMPRESSED),
        .VEnable        (VEnable),
        .VLEN           (VLEN),
        .BRANCHPRED     (BRANCHPRED)
    ) dut (
        .clk                    (clk),
        .reset_n                (reset_n),
        .sys_reset_i            (1'b0),
        .stall                  (stall),
        .instruction_i          (cpu_instruction),
        .mem_data_i             (cpu_data_in),
        .mtime_i                (mtime),
        .irq_i                  (irq),
        .instruction_address_o  (cpu_instruction_address),
        .mem_operation_enable_o (cpu_operation_enable),
        .mem_write_enable_o     (cpu_write_enable),
        .mem_address_o          (cpu_data_address),
        .mem_data_o             (cpu_data_out),
        .interrupt_ack_o        (interrupt_ack)
    );
    
    // Instanciação do periférico sniffer
    sniffer Sniffer1 (
        .clk            (clk),
        .reset_n        (reset_n),
        .enable_i       (enable_peripherals_r),
        .write_enable_i (cpu_write_enable),
        .data_address_i (cpu_data_address),
        .data_i         (cpu_data_out),
        .data_o         (data_peripherals)
    );
    
    BRAM RAM (
        .clka   (clk),                      // input wire clka
        .ena    (!stall),                   // input wire ena
        .wea    (4'h0),                     // input wire [3 : 0] wea
        .addra  (cpu_instruction_address),  // input wire [31 : 0] addra
        .dina   (0),                        // input wire [31 : 0] dina
        .douta  (cpu_instruction),          // output wire [31 : 0] douta
        //////////////////////////////////////////////////////
        .clkb   (clk),                      // input wire clkb
        .enb    (enable_ram),               // input wire enb
        .web    (cpu_write_enable),         // input wire [3 : 0] web
        .addrb  (cpu_data_address),         // input wire [31 : 0] addrb
        .dinb   (cpu_data_out),             // input wire [31 : 0] dinb
        .doutb  (data_bram)                 // output wire [31 : 0] doutb
    );

    initial begin
        clk = 1;
        forever #5 clk = ~clk;
    end

    initial begin
        stall = 0;
    end
    
    
    initial begin
    reset_n = 0;
    #200;
    reset_n = 1;
    end

//    always_ff @(posedge clk) begin
//        if ((write_enable_i != 0) && (enable_peripherals == 1) && (cpu_data_address == 32'h80000003)) // Simply checks if A equals B
//        assert (cpu_data_address != 1000) $display ("O contador chegou a 1000");
//    end
endmodule