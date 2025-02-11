#include "../../common/include/riscv-csr.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>

static inline void print_binary(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        // Verifica se o bit i está setado e imprime '1' ou '0'
        putchar((num & (1u << i)) ? '1' : '0');
    }
    putchar('\n');
}

static inline void nop(){
    __asm__ volatile("nop");
}

int main()
{
    nop();

    //printf("Hello World!\n");

    // uint32_t data = 0xFFFFFFFF;
    
    // // Loop que continua enquanto 'data' for diferente de 0
    // while (data != 0) {
    //     // Imprime a representação binária de 'data'
    //     print_binary(data);

    //     // Desloca os bits para a esquerda (inserindo 0 no bit menos significativo)
    //     data = data << 1;
    // }

    // Lê o contador de ciclos (mcycle)
    uint32_t mcycle_value;
    mcycle_value = csr_read_mcycle();

    uint_xlen_t read_cycle_value;
    read_cycle_value = csr_read_cycle();
    
    // Imprime o valor lido.
    printf("\nmcycle: %lu", mcycle_value);
    printf("\nread cycle: %lu", read_cycle_value);

    return 0;
}
