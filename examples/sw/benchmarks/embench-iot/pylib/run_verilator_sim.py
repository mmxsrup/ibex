__all__ = [
    'get_target_args',
    'build_benchmark_cmd',
    'decode_results',
]

import argparse
import csv
import os.path

from embench_core import log


def get_target_args(remnant):
    """Parse left over arguments"""
    parser = argparse.ArgumentParser(description='Get target specific args')

    parser.add_argument(
        '--verilator-sim',
        type=str,
        required=True,
        help='Path to verilator sim binary',
    )

    return parser.parse_args(remnant)


def build_benchmark_cmd(bench, args):
    """Construct the command to run the benchmark.  "args" is a
       namespace with target specific arguments"""
    cmd = [f'{args.verilator_sim}',
           f'--raminit={bench}.vmem']

    return cmd


def decode_results(stdout_str, stderr_str, bench, appdir):
    """Extract the results from the output string of the run. Return the
       elapsed time in milliseconds or zero if the run failed."""

    pcount_csv_filename = os.path.join(appdir, 'ibex_simple_system_pcount.csv')

    log.debug(f'Looking for {bench} results in {pcount_csv_filename}')

    try:
        with open(pcount_csv_filename, newline='') as pcount_csvfile:
            pcount_csv_reader = csv.reader(pcount_csvfile)
            for pcount_row in pcount_csv_reader:
                if(pcount_row[0] == 'Cycles'):
                    cycle_count = int(pcount_row[1])
                    return cycle_count / 1000.0
    except FileNotFoundError:
        log.warning(f'Could not find {pcount_csv_filename}')

    return 0.0
