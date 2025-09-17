# STM32F401RE BAREMETAL UART DRIVER

## Overview

**Polling implementation of a UART Driver**
Currently supports:
- Customizable baud rate without any added calculations
- Functionality for sending serial data through printf
- Functionality to receive data

Next Steps:
- To add interrupt based logic
- Explore DMA alternatives

## Hardware and Tools
- Board: STM32F401RE (Nucleo Board)
- Toolchain: STM32CubeIDE
- Serial Monitor: PuTTY/Picocom

## Usage
1. Clone this repo
2. Open in STM32CubeIDE
3. Build and flash to STM32F401RE
4. Open serial monitor at 115200 baud
5. Type characters -> board echoes them back

## Learnings
- How to configure UART registers directly (without HAL)
- Proper baudrate calculations
- Importance of using integer/fixed point math instead of floating point
- Usage of fixed point math and implementing it by calculating mantissa and fraction (BRR register)
- Usage and importance of oversampling (8x and 16x) in accurate UART communication

## References
- STM32 documentation (datasheets, user guide, reference manual)
