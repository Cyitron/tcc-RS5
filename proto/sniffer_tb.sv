`timescale 1ns/1ps

module tb_sniffer;

  // Sinais do testbench
  logic clk;
  logic reset_n;
  logic enable_i;
  logic [3:0] write_enable_i;
  logic [31:0] data_address_i;
  logic [31:0] data_i;
  logic [31:0] data_o;  // Saída do sniffer

  // Geração de clock: período de 10 ns
  initial begin
    clk = 0;
    forever #5 clk = ~clk;
  end

  // Geração de reset
  initial begin
    reset_n = 0;
    #20;
    reset_n = 1;
  end

  // Instanciação do periférico sniffer
  sniffer Sniffer1 (
    .clk            (clk),
    .reset_n        (reset_n),
    .enable_i       (enable_i),
    .write_enable_i (write_enable_i),
    .data_address_i (data_address_i),
    .data_i         (data_i),
    .data_o         (data_o)
  );

  // Sequência de estímulo para testar a lógica do sniffer
  initial begin
    // Inicializa os sinais
    enable_i = 0;
    write_enable_i = 4'b0000;
    data_address_i = 32'h00000000;
    data_i = 32'h00000000;

    // Aguarda reset
    #30;

    // Simula uma operação de escrita que NÃO é direcionada ao sniffer:
    // (por exemplo, endereço abaixo de 0x8...)
    enable_i = 1;
    write_enable_i = 4'b1111;
    data_address_i = 32'h70000000;  // endereço fora da faixa (menos que 4'h8 no nibble MSB)
    data_i = 32'h12345678;
    #1
    $display("Data ready  : 0x%h", data_o);
    #10;

    // Agora, simula uma operação de escrita direcionada ao sniffer:
    // Sinaliza que o processador está escrevendo para o periférico, 
    // que deve capturar e inverter o dado.
    data_address_i = 32'h80000000;  // endereço com nibble MSB >= 8
    data_i = 32'h12345678;
    write_enable_i = 4'b0001;        // operação de escrita válida
    #10;

    // Aguarda alguns ciclos para que o sniffer processe o dado.
    #20;

    // Simula o processador lendo o dado pronto:
    // Para este teste, podemos alterar o data_address_i para o endereço que indica a leitura.
    data_address_i = 32'h80000002;   // exemplo de endereço que sinaliza a leitura concluída
    #1;
    $display("Data ready  : 0x%h", data_o);


    data_address_i = 32'h80000001;
    #1
    // Exibe o resultado no simulador
    $display("Data In   : 0x%h", data_i);
    $display("Data Out  : 0x%h", data_o);

    // Finaliza a simulação
    #50;
    $finish;
  end

endmodule
