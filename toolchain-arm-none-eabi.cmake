set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)

# Prevent CMake from trying to link test executables during compiler detection
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Point to newlib headers bundled with arm-none-eabi-gcc
execute_process(COMMAND arm-none-eabi-gcc -print-sysroot
  OUTPUT_VARIABLE ARM_SYSROOT OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_SYSROOT ${ARM_SYSROOT})
