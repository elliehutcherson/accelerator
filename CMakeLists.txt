cmake_minimum_required(VERSION 3.15)

# Tell CMake we're cross-compiling
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# Specify the cross compiler
set(CMAKE_C_COMPILER /usr/local/bin/avr-gcc)
set(CMAKE_CXX_COMPILER /usr/local/bin/avr-g++)

# Don't try to test the compiler (it needs special flags for AVR targets)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# Disable macOS-specific linker flags
set(CMAKE_C_LINK_FLAGS "")
set(CMAKE_CXX_LINK_FLAGS "")

project(accelerator C CXX)

# Target microcontroller and clock speed
set(MCU atmega328p)
set(F_CPU 16000000UL)

# Compiler flags
set(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}")

# Include directories from avr-libc submodule
include_directories(
    ${CMAKE_SOURCE_DIR}/include/avr-libc/include
)

# Source files
set(SOURCES
    blink.cc
)

# Create executable
add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Generate hex file
add_custom_command(
    TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-objcopy -O ihex -R .eeprom ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMENT "Creating hex file"
)

# Generate size information
add_custom_command(
    TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-size --format=avr --mcu=${MCU} ${PROJECT_NAME}.elf
    COMMENT "Size information"
)