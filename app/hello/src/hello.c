#include "../../common/include/riscv-csr.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>

uint32_t mcycle_value;
uint32_t m_inst_retired;
uint_xlen_t mhpmcounter3;
uint_xlen_t mhpmcounter4;
uint_xlen_t mhpmcounter31;
uint_xlen_t hpmcounter3;
uint_xlen_t hpmcounter4;
uint_xlen_t hpmcounter31;
uint_xlen_t mpec;
uint_xlen_t upec;
uint_xlen_t read_cycle_value;
uint_xlen_t instret;

static inline void print_binary(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        // Verifica se o bit i está setado e imprime '1' ou '0'
        putchar((num & (1u << i)) ? '1' : '0');
    }
    putchar('\n');
}

int main()
{
    //nop();

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
    mcycle_value = csr_read_mcycle();

    //funções executudas com sucesso pela CPU (retired)
    m_inst_retired = csr_read_minstret();

    // Machine performance-monitoring counter
    mhpmcounter3 = csr_read_mhpmcounter3();
    mhpmcounter4 = csr_read_mhpmcounter4();
    mhpmcounter31 = csr_read_mhpmcounter31();

    // Machine Exception Program Counter
    mpec = csr_read_mepc();

    // User Exception Program Counter
    upec =  csr_read_uepc();

    // Cycle counter for RDCYCLE instruction
    read_cycle_value = csr_read_cycle();

    // Instructions-retired counter for RDINSTRET instruction
    instret = csr_read_instret();

    // Performance-monitoring counter
    hpmcounter3 = csr_read_hpmcounter3();
    hpmcounter4 = csr_read_hpmcounter4();
    hpmcounter31 = csr_read_hpmcounter31();

    // Imprime o valor lido.
    printf("\nmcycle: %lu", mcycle_value);
    printf("\nRD cycle: %lu", read_cycle_value);
    printf("\nminstret: %lu", m_inst_retired);
    printf("\nmhpmcounter3: %lu", mhpmcounter3);
    printf("\nmhpmcounter4: %lu", mhpmcounter4);
    printf("\nmhpmcounter31: %lu", mhpmcounter31);
    printf("\nmepc: %lu", mpec);
    printf("\nuepc: %lu", upec);
    printf("\ninstret: %lu", instret);
    printf("\nhpmcounter3: %lu", hpmcounter3);
    printf("\nhpmcounter4: %lu", hpmcounter4);
    printf("\nhpmcounter31: %lu", hpmcounter31);

    return 0;
}

//==========================//
// static inline void nop(){
//     __asm__ volatile("nop");
// }