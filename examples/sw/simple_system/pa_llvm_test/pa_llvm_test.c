// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include "simple_system_common.h"

#define PMP_NAPOT 0x18
#define PMP_R 0x01
#define PMP_W 0x02
#define PMP_X 0x04

#define MSTATUS_MPP_M (3 << 11)
#define MSTATUS_MPP_U (0 << 11)

void test(void);

__attribute__ ((target("sign-return-address=none")))
void setup_pakey() {
  // Set the key for PA in CSR
  uint32_t key = 0xdeadbeef;
  asm volatile(
      "csrw 0x7c2, %[key];"
      "csrw 0x7c3, %[key];"
      "csrw 0x7c4, %[key];"
      "csrw 0x7c5, %[key];"
      :
      : [key] "r"(key)
      :);
}

__attribute__ ((target("sign-return-address=none")))
void setup_pmp() {
  // 0x00000000 ~ 0x0FFFFFFF is accessible
  uint32_t base_addr = 0x0;
  uint32_t size = 1 << 30;
  uint32_t napot_size = (size / 2) - 1;
  uint32_t pmpaddr = (base_addr + napot_size) >> 2;
  uint32_t pmpcfg = PMP_NAPOT | PMP_R | PMP_W | PMP_X;
  asm volatile(
      "csrw pmpaddr0, %0;"
      "csrw pmpcfg0, %1;"
      :
      : "r"(pmpaddr), "r"(pmpcfg)
      :);
}

int foo(int x) {
  puts("Foo function\n");
  return x + 1;
}

int crash(int x) {
  puts("Crash function\n");
  asm("sw %0, 4(s0)" :: "r"(0xEEEEEEEE));
  puts("Rewrite return address\n");
  return x + 1;
}

void test() {
  foo(41);
  crash(41);

  // Stop simulation
  sim_halt();
}

__attribute__ ((target("sign-return-address=none")))
int main(int argc, char **argv) {
  setup_pakey();
  setup_pmp();
  puts("End setup");
  // from M mode to U mode
  uint32_t mstatus;
  asm volatile("csrr %0, mstatus" : "=r"(mstatus));
  mstatus = (mstatus & ~MSTATUS_MPP_M) | MSTATUS_MPP_U;
  asm volatile(
      "csrw mstatus, %0;"
      "csrw mepc, %1;"
      "mret;"
      :
      : "r"(mstatus), "r"(test));
  return 0;
}
