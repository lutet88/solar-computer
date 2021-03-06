cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

set(PICO_BOARD adafruit_itsybitsy_rp2040)

project(firmware C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(firmware
    main.c graphics.c fonts.c keyboard.c utils.c terminal.c commands.c
)

pico_enable_stdio_usb(firmware 1)
pico_enable_stdio_uart(firmware 0)

pico_add_extra_outputs(firmware)

add_subdirectory(no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)

target_link_libraries(firmware pico_stdlib hardware_gpio hardware_uart hardware_spi FatFs_SPI)
