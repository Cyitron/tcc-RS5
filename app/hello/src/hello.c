#include "../../common/include/riscv-csr.h"
#include <stdio.h>
#include <inttypes.h>

int main()
{
    uint64_t minstret_value = csr_read_minstret();
    printf("Hello World!\n");

    // Teste imprimindo um valor fixo
    printf("Teste de uint64_t: %" PRIu64 "\n", (uint64_t) 1234567890);

    // Agora imprime o minstret
    printf("minstret: %" PRIu64 "\n", minstret_value);

    return 0;
}
