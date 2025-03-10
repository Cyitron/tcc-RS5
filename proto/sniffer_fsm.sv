module sniffer_fsm (
    .clk
    .reset_n,
    .ena_1,
    .ena_2
    .data_address_i,
    .enable_i

);


    input  logic            clk;
    input  logic            reset_n;
    output logic            ena_1;
    output logic            ena_2;
    input  logic[31:0]      data_address_i;
    input  logic            enable_i;

    reg state;
    reg nex_state;

    localparam s_0         = 2'b00;
    localparam s_1         = 2'b01;
    localparam s_2         = 2'b10;
    localparam s_3         = 2'b11;

    always@(posedge clk) begin
        if (reset_n == 0)
            state = s_0;
        else
            state = next_state;
    end

    always@(posedge clk) begin
        case (data_address_i[31:28])
        s_0: if (data_address_i[31:28] >= 4'h8) next_state = s_1;
        s_1: next_state = s_2;
        s_2: next_state = s_3;
        s_3: next_state = s_0;
        default:
        endcase
    
    end

always @(state) begin
    case (state)

    s_0: begin
        ena_1 = 0;
        ena_2 = 0;
    end

    s_1: begin
        ena_1 = 1;
        ena_2 = 0;
    end

    s_2: begin
        ena_1 = 0;
        ena_2 = 1;
    end

    s_3: begin
        ena_1 = 0;
        ena_2 = 0;
    end

    

    endcase

end



endmodule