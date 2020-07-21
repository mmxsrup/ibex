// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include "simple_system_common.h"

int foo(int x) {
  puts("Foo function\n");
  return x + 1;
}

int crash(int x) {
  puts("Crash function\n");
  volatile char buf[16];
  for (int i = 0; i < 32; ++i) { // <- Bug
    buf[i] = 'A';
  }
  puts("Buffer overflow\n");
  return x + 1;
}

void test() {
  foo(41);
  crash(41);

  // Stop simulation
  sim_halt();
}
