module sniffer_fsm (
    input  logic            clk,
    input  logic            reset_n,
    output logic            ena_1,
    output logic            ena_2,
    input  logic[31:0]      data_address_i,
    input  logic            enable_i

);

    /* flip-flop com chip_enable para saber que teve escrita no segundo registrador e depois
    software faz pooling no flip-flop depois de escrever o dado do periferico

    mux seletor saida tristate

    */

    

    // testar os 4 bits mais significativos são maiores que 8 seguidos de 7 zeros 
    

    reg state;
    reg next_state;

    localparam s_0         = 2'b00;
    localparam s_1         = 2'b01;
    localparam s_2         = 2'b10;
    localparam s_3         = 2'b11;

    always @(posedge clk) begin
        if (reset_n == 0) begin
            state = s_0;
        end
        else begin
            state = next_state;
        end
    end

    always @(posedge clk) begin
        case (data_address_i[31:28])
            s_0: begin
                if (data_address_i[31:28] >= 4'h8)
                    next_state = s_1;
            end
            s_1: next_state = s_2;
            s_2: next_state = s_3;
            s_3: next_state = s_0;
            default: next_state = s_0;  // estado padrao no reset
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