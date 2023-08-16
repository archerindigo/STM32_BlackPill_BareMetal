# Bare Metal ARM Programming with STM32 Black Pill and libopencm3

This repository contains code I generated during my exploration of STM32 programming using STM32 Black Pill libopencm3. You're welcome to clone this repository, go through the commits and my blog posts to learn step by step together.

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

## Build Applications

Each application project is stored in separated directory with the prefix `app_`. Each project contains its own Makefile to build the binaries. From the root directory of the workspace, you may make with:

```
make -C app_xxx
```

All binaries will be located in the directory `bin/` within the project.

If the firmware is to be flashed on a different MCU other than `stm32f411ceu6`, update the `DEVICE` variable in the Makefile accordingly in order to build the correct binaries.

At the moment there is no top-level Makefile to build all projects at once.
