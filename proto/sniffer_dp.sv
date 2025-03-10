module sniffer_dp (
    .clk,
    .reset_n,
    .data_i,
    .data_o,
    .ena_1,
    .ena_2

);

    input  logic            clk;
    input  logic            reset_n;
    input  logic [31:0]     data_i;
    output logic [31:0]     data_o;
    input  logic            ena_1;
    input  logic            ena_2;

    
    logic [31:0] data_snf_1;
    logic [31:0] data_snf_2;

    always_ff @(posedge clk) begin
        if (ena_1) begin
            data_snf_1 = ~(data_i);
        end
        else begin
            data_snf_1 = data_snf_1;
        end
    end

    always_ff @(posedge clk) begin
        if (ena_2) begin
            data_snf_2 = data_snf_1;
        end
        else begin
            data_snf_2 = data_snf_2;
        end
    end

endmodule