#  Ibex Pointer Authentication Test

Ibex Pointer Authentication Test is an application to test pac/aut instructions
added for pointer authentication. This test confirms that pac/aut instructions can be executed correctly.
In addition, the test intentionally rewrites the return address and
verifies if an exception occurs when the function returns.
We are using Ibex Simple System, so see `examples/simple_system/README.md` for more details.

## Prerequisites

Basically, you need the prerequisites written `examples/simple_system/README.md`.
In addition, you need a llvm compiler that supports pointer authentication.
TODO: How to get llvm

## Building Simulation

The Simple System simulator binary can be built via FuseSoC. From the Ibex repository root run:

```
fusesoc --cores-root=. run --target=sim --setup --build lowrisc:ibex:ibex_simple_system --RV32M=1 --RV32E=0 --PMPEnable=1 --PointerAuthentication=1
```

## Building Software

To build the pointer authentication example, from the Ibex reposistory root run:

```
make -C examples/sw/simple_system/pa_llvm_test CC=/home/srup/gsoc/llvm-project/build/bin/clang XCFLAGS='--sysroot=/tools/riscv/riscv32-unknown-elf --gcc-toolchain=/tools/riscv'
```

## Running the Simulator

Having built the simulator and software, from the Ibex repository root run:

```
./build/lowrisc_ibex_ibex_simple_system_0/sim-verilator/Vibex_simple_system -t --meminit=ram,./examples/sw/simple_system/pa_test_llvm/pa_test_llvm.elf
```

Outputting some simulation statistics:

```
TODO
```

The simulator produces several output files

* `ibex_simple_system.log` - The ASCII output written via the output peripheral
* `ibex_simple_system_pcount.csv` - A csv of the performance counters
* `trace_core_00000000.log` - An instruction trace of execution

By see `ibex_simple_system.log`, you can confirm that the exception is occurring:

```
TODO
```
