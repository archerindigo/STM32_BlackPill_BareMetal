# Bare Metal ARM Programming with STM32 Black Pill and libopencm3

This repository contains code I generated during my exploration of STM32 programming using WeAct Black Pill STM32F411 and libopencm3. You're welcome to clone this repository, go through the commits and my [blog posts](https://bluebirdbeats.com/category/%E9%9B%BB%E8%85%A6%E7%A7%91%E6%8A%80/discover-stm32-with-libopencm3/) to learn step by step together.

The studying is still in progress, so the repository should update from time to time.

## Installation

The development environment was built from my Manjaro Linux machine and Visual Studio Code is the main editor I use in this project. Your machine should have the following packages (or equivalent) installed:

- git
- make
- arm-none-eabi-gcc
- arm-none-eabi-newlib
- dfu-util

For VS Code, it is recommended to install the `C/C++` extension pack to allow proper code inspection.

The repository contains the libopencm3 as a submodule, so please use the following command to clone everything:

```
git clone --recurse-submodules https://github.com/archerindigo/STM32_BlackPill_BareMetal.git
```

## Build the Applications

Each application project is stored in separated directory with the prefix `app_`. Each project contains its own Makefile to build the binaries. From the root directory of the workspace, you may make with:

```
make -C app_xxx
```

All binaries will be located in the directory `bin/` within the project.

If the firmware is to be flashed on a different MCU other than `stm32f411ceu6`, update the `DEVICE` variable in the Makefile accordingly in order to build the correct binaries.

At the moment there is no top-level Makefile to build all projects at once.

## Flash the Binary

Currently I am using `dtu-util` to flash the binary. Any other STM32 flashing tool such as STM32CubeProgrammer will also do.

To set the Black Pill into DFU mode, press `NRST` button while holding `BOOT0` button.

`dfu-util -l` should be about to detect the board. Check the `alt` number of the internal flash partition. At my side it is always `0`

Then you should flash the binary into the flash part of the memory with the starting address `0x08000000`:

```
dfu-util -a 0 -D <app>.bin -s 0x08000000
```
