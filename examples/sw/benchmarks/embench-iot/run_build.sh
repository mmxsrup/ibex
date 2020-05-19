#!/bin/bash

pushd ./config/riscv32/boards/ibex_ss_verilator
make lib
popd

./build_all.py  --arch riscv32 --chip speed-test --board ibex_ss_verilator --cc riscv32-unknown-elf-gcc --ld riscv32-unknown-elf-gcc --verbose
