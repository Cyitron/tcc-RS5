#include "../../common/include/riscv-csr.h"
#include <stdio.h>

int main()
{
    printf("\nHello World!\n");

    uint64_t minstret_value = csr_read_minstret();
    printf("minstret: %llu\n", minstret_value);

    return 0;
}
