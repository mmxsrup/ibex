#!/bin/sh

./benchmark_speed.py --target-module run_verilator_sim --verilator-sim \
`pwd`/../../../../build/lowrisc_ibex_ibex_simple_system_0/sim-verilator/Vibex_simple_system
