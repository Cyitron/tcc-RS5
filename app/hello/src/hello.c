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

int main()
{
    //uint64_t csr_read_mcycle = csr_read_minstret();
    printf("Hello World!\n");

    uint32_t data = 0xFFFFFFFF;
    
    // Loop que continua enquanto 'data' for diferente de 0
    while (data != 0) {
        // Imprime a representação binária de 'data'
        print_binary(data);

        // Desloca os bits para a esquerda (inserindo 0 no bit menos significativo)
        data = data << 1;
    }

    // Lê o contador de ciclos (mcycle)
    uint64_t mcycle_value;
    mcycle_value = csr_read_mcycle();

    // uint_xlen_t read_cycle_value;
    // read_cycle_value = csr_read_cycle();
    
    // Imprime o valor lido. Usamos PRIu64 para portabilidade.
    printf("mcycle: %llu", mcycle_value + 1);
    //printf("read cycle: %llu", read_cycle_value);

    return 0;
}
