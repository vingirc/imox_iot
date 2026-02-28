#!/bin/bash

CYAN='\033[0;36m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${CYAN}--- Iniciando Simulador de Interfaz ---${NC}"

cd simulador || { echo -e "${RED}Error: No se encontro la carpeta 'simulador'${NC}"; exit 1; }

if [ ! -d "build" ]; then
    mkdir build
fi
cd build

echo -e "${YELLOW}Configurando entorno (CMake)...${NC}"
cmake .. > /dev/null

echo -e "${YELLOW}Compilando...${NC}"
cmake --build .

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Compilacion exitosa. Abriendo ejecutable...${NC}"
    # Ejecutar el binario generado
    ../bin/main
else
    echo -e "${RED}Error durante la compilacion. Revisa los logs.${NC}"
    exit 1
fi
