#!/bin/sh
set -x

riscv32-unknown-elf-objdump -fhSD $1 > $1.dis
riscv32-unknown-elf-objcopy -O binary $1 $1.bin
srec_cat $1.bin -binary -offset 0x0000 -byte-swap 4 -o $1.vmem -vmem

