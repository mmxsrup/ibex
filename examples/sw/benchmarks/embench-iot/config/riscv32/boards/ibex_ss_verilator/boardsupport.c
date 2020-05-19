/* Copyright (C) 2017 Embecosm Limited and University of Bristol

   Contributor Graham Markall <graham.markall@embecosm.com>

   This file is part of Embench and was formerly part of the Bristol/Embecosm
   Embedded Benchmark Suite.

   SPDX-License-Identifier: GPL-3.0-or-later */

#include <support.h>
#include "simple_system_common.h"

void
initialise_board ()
{
  puts("EMBench running\n");
}

void __attribute__ ((noinline)) __attribute__ ((externally_visible))
start_trigger ()
{
  puts("Start bench\n");
  pcount_enable(0);
  pcount_reset();
  pcount_enable(1);
}

void __attribute__ ((noinline)) __attribute__ ((externally_visible))
stop_trigger ()
{
  pcount_enable(0);
  puts("Stop bench\n");
}
