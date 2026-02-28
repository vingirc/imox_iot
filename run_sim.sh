#!/bin/bash

CYAN='\033[0;36m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${CYAN}--- Iniciando Simulador de Interfaz ---${NC}"

# 1. Regresar la configuracion de color a la normalidad para la PC
sed -i 's/#define LV_COLOR_16_SWAP .*/#define LV_COLOR_16_SWAP 0/' simulador/lv_conf.h

# 2. Truco: Convertir los bloqueos de SquareLine en simples advertencias
if [ -f "src/ui/ui.c" ]; then
    sed -i 's/#error "LV_COLOR_16_SWAP/#warning "LV_COLOR_16_SWAP/g' src/ui/ui.c
    sed -i 's/#error "LV_COLOR_DEPTH/#warning "LV_COLOR_DEPTH/g' src/ui/ui.c
fi

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
    ../bin/main
else
    echo -e "${RED}Error durante la compilacion. Revisa los logs.${NC}"
    exit 1
fi
