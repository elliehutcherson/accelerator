cmake_minimum_required(VERSION 3.15)

# Tell CMake we're cross-compiling
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# Specify the cross compiler
set(CMAKE_C_COMPILER /usr/local/bin/avr-gcc)
set(CMAKE_CXX_COMPILER /usr/local/bin/avr-g++)
set(CMAKE_ASM_COMPILER /usr/local/bin/avr-gcc)

# Don't try to test the compiler (it needs special flags for AVR targets)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# Disable macOS-specific linker flags
set(CMAKE_C_LINK_FLAGS "")
set(CMAKE_CXX_LINK_FLAGS "")

# Enable generation of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(accelerator C CXX)

# Target microcontroller and clock speed
set(MCU atmega328p)
set(F_CPU 16000000UL)

# Compiler flags
# set(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall -Wextra")
# set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}")
set(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall -Wextra")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}")

# Include directories from avr-libc submodule
include_directories(
    ${CMAKE_SOURCE_DIR}/include/avr-libc/include
)

# Blink source files
set(BLINK_SOURCES
    blink.cc
)

# Create blink executable
add_executable(blink.elf ${BLINK_SOURCES})

# Generate hex file
add_custom_command(
    TARGET blink.elf POST_BUILD
    COMMAND avr-objcopy -O ihex -R .eeprom blink.elf blink.hex
    COMMENT "Creating hex file"
)

# Generate size information
add_custom_command(
    TARGET blink.elf POST_BUILD
    COMMAND avr-size --format=avr --mcu=${MCU} blink.elf
    COMMENT "Size information"
)

# Upload target (optional)
add_custom_target(upload
    COMMAND avrdude -c arduino -p ${MCU} -P /dev/tty.usbmodem14101 -b 115200 -U flash:w:blink.hex
    DEPENDS blink.elf
    COMMENT "Uploading to Arduino"
)

# Toggle source files
set(TOGGLE_SOURCES
    toggle.cc
)

# Create toggle executable
add_executable(toggle.elf ${TOGGLE_SOURCES})

# Generate hex file for toggle
add_custom_command(
    TARGET toggle.elf POST_BUILD
    COMMAND avr-objcopy -O ihex -R .eeprom toggle.elf toggle.hex
    COMMENT "Creating hex file for toggle"
)

# Generate size information for toggle
add_custom_command(
    TARGET toggle.elf POST_BUILD
    COMMAND avr-size --format=avr --mcu=${MCU} toggle.elf
    COMMENT "Size information for toggle"
)

# Upload target for toggle (optional)
add_custom_target(upload_toggle
    COMMAND avrdude -c arduino -p ${MCU} -P /dev/tty.usbmodem14101 -b 115200 -U flash:w:toggle.hex
    DEPENDS toggle.elf
    COMMENT "Uploading toggle to Arduino"
)