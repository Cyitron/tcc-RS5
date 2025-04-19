#!/bin/bash

# Habilitar "exit on error" para parar caso algum comando falhe
set -e

# Navegar para o diretório do projeto
cd app/write_peripheral/

# Limpar e compilar o projeto
make clean
make

# Navegar para o diretório proto
cd ../../proto

# Inicializar a memória com o binário gerado
./init_mem.py ../app/write_peripheral/write_peripheral.bin

# Retornar ao diretório original
cd ../

echo "Script concluído com sucesso!"
