# CS704 SW

CS704 Software Base Project. Provides basic firmware for the AWSAM5_CS704 board.  
This also includes the beacon module as installed on the test environment nodes.  

## Overview

The application is built using a [makefile](Makefile), which also provides shortcuts for common functions.
Application components are located in [app](/app), processor support is in [stm32l1](/stm32l1).
Modules and drivers are included as git submodules in [modules](/modules).

## Requirements

 - make
 - gcc-arm-none-eabi
 - texane/stlink
 - dfu-util

## Usage

 - `make` to build
 - `make dfu` to flash via DFU
 - `make flash` to flash via stlink
 - `make clean` to clean
 - `make ds` to launch debug server
 - `make d` to launch gdb session


------

If you have any questions, comments, or suggestions, feel free to open an issue or a pull request.
