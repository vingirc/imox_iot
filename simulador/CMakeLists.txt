cmake_minimum_required(VERSION 3.10)
project(lvgl_sim)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# --- CONFIGURACIONES GLOBALES (SINCRONIZA LA VENTANA CON LVGL) ---
include_directories(${PROJECT_SOURCE_DIR})
add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)
add_compile_definitions(LV_DRV_CONF_INCLUDE_SIMPLE)

# Forzar el tamaño exacto de la ventana para tu AMOLED (536x240)
add_compile_definitions(SDL_HOR_RES=536)
add_compile_definitions(SDL_VER_RES=240)
add_compile_definitions(SDL_ZOOM=1)

# Ignorar la advertencia estricta de SquareLine en la PC
add_compile_options(-Wno-error)
# -----------------------------------------------------------------

# Agregar el motor de LVGL y los drivers de PC (SDL)
add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

find_package(SDL2 REQUIRED)

# Buscar recursivamente todos tus archivos exportados
file(GLOB_RECURSE UI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/ui/*.c")

set(MAIN_SOURCES main.c)

add_executable(main ${MAIN_SOURCES} ${UI_SOURCES})

target_include_directories(main PRIVATE 
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

target_link_libraries(main lvgl lv_drivers ${SDL2_LIBRARIES} m)