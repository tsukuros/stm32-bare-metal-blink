cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(blink C ASM)

set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

set(CMAKE_C_FLAGS "${MCU_FLAGS} -Wall -O0 -g3")
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -T${CMAKE_SOURCE_DIR}/STM32F446RETX_FLASH.ld -nostdlib --specs=nano.specs -Wl,--gc-sections")

add_executable(blink src/main.c startup_stm32f446xx.s)
target_include_directories(blink PRIVATE include)
target_compile_definitions(blink PRIVATE STM32F446xx)
