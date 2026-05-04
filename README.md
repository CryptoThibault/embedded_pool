# Embedded Pool

This repository is an introduction to embedded systems through a sequence of AVR microcontroller exercises. Each module focuses on a core embedded topic, and each exercise explores that topic with concrete hardware examples: LEDs, buttons, timers, UART, ADC, I2C, SPI, EEPROM, and event-driven interaction.

## Table of Contents

- [Overview](#overview)
- [Module 00: Basic I/O](#module-00-basic-io)
- [Module 01: Timer and PWM](#module-01-timer-and-pwm)
- [Module 02: UART and Interrupts](#module-02-uart-and-interrupts)
- [Module 03: RGB LEDs and User Input](#module-03-rgb-leds-and-user-input)
- [Module 04: Interrupts and Debounce](#module-04-interrupts-and-debounce)
- [Module 05: ADC and UART Monitoring](#module-05-adc-and-uart-monitoring)
- [Module 06: I2C and Sensor Interface](#module-06-i2c-and-sensor-interface)
- [Module 07: EEPROM and Command Interface](#module-07-eeprom-and-command-interface)
- [Module 08: SPI RGB Control](#module-08-spi-rgb-control)
- [Module 09: I2C Expander and Displays](#module-09-i2c-expander-and-displays)
- [Rush00](#rush00)
- [Rush01](#rush01)
- [How to Run](#how-to-run)

## Overview

The project is organized into ten learning modules and two rush projects. Each module contains small exercises that build practical skills in embedded programming using AVR hardware. The exercises are designed to show how microcontroller peripherals work in isolation and how they can be combined into more advanced systems.

### Module 00: Basic I/O

This module introduces fundamental GPIO control on AVR hardware. It covers setting pins as outputs and inputs, reading button state, using pull-up resistors, and simple LED display techniques.

### Module 01: Timer and PWM

Module 01 focuses on AVR timer peripherals. It demonstrates software blinking, timer compare operations, PWM generation, and interactive brightness control.

### Module 02: UART and Interrupts

This module explores serial communication and interrupt-driven behavior. It includes UART initialization, data transmission, input handling, and using interrupts for periodic and asynchronous tasks.

### Module 03: RGB LEDs and User Input

Module 03 combines RGB LED control with user interaction. It shows multi-channel PWM, color generation, and parsing commands from UART to change LED output dynamically.

### Module 04: Interrupts and Debounce

This module emphasizes interrupt-based event handling and debouncing. It uses external interrupts, timer-based debounce, and interrupts to manage button actions and LED state.

### Module 05: ADC and UART Monitoring

Module 05 covers analog sensing and serial reporting. It uses the ADC to read voltages, temperature, and sensor inputs, and outputs results over UART for observation.

### Module 06: I2C and Sensor Interface

This module introduces I2C communication with peripheral sensors. It shows how to initialize the I2C bus, send commands, and read data from an environmental sensor.

### Module 07: EEPROM and Command Interface

Module 07 works with non-volatile storage and command parsing. It demonstrates EEPROM access, data persistence, and a UART-based command interface for configuration and debugging.

### Module 08: SPI RGB Control

This module explores SPI communication and RGB driver patterns. It uses SPI to control LED chains, color modes, and responsive display behavior tied to ADC input and commands.

### Module 09: I2C Expander and Displays

Module 09 uses an I2C port expander and display peripherals. It covers remote GPIO control, button scanning, 7-segment display driving, and combining sensors with expander outputs.

### Rush00

Rush00 is an embedded game platform that synchronizes gameplay between two AVR boards using I2C communication. It features button-driven interactions, timer-based event scheduling, state management for idle, timing, and finish events, and demonstrates responsive event loops integrating user input, timers, and inter-board synchronization.

### Rush01

Rush01 is a comprehensive integration project that tests various board functionalities, including UART command handling, LED and RGB control (using SPI for certain LEDs), ADC input, I2C communication with peripherals like the RTC (real-time clock) and AHT20 environmental sensor, expander management for displays and inputs, timer-based updates, and button event processing. It serves as a practical example of a full embedded system combining multiple peripherals.

## How to Run

1. Choose a module and exercise directory, for example:
   - `cd module03/ex03`
   - `cd rush00`
   - `cd rush01`

2. Build the exercise:
   - `make`

3. If the directory supports flashing to hardware, use:
   - `make flash`

4. For UART-based exercises, connect to the board serial port and use a terminal at `115200` baud.

5. If needed, inspect output files in the exercise directory after build:
   - `*.hex` or `*.elf`

> Note: all module exercises are written for AVR microcontrollers and use local Makefiles for build and flash operations.
