#!/bin/bash

# Habilitar "exit on error" para parar caso algum comando falhe
set -e

# Navegar para o diretório do projeto
cd app/hello/

# Limpar e compilar o projeto
make clean
make

# Navegar para o diretório proto
cd ../../proto

# Inicializar a memória com o binário gerado
./init_mem.py ../app/hello/hello.bin

# Retornar ao diretório original
cd ../

echo "Script concluído com sucesso!"
