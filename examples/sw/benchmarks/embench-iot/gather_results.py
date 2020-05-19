import pathlib
import csv
import argparse

def get_pcount_paths(embench_run_dir):
    embench_root = pathlib.Path(embench_run_dir)
    embench_run_dirs = [p for p in embench_root.iterdir() if p.is_dir()]

    pcount_paths = {}

    for embench_run_dir in embench_run_dirs:
        pcount_path = embench_run_dir / 'ibex_simple_system_pcount.csv'
        if pcount_path.exists():
            pcount_paths[embench_run_dir.name] = pcount_path
        else:
            print('WARNING: Could not find pcount CSV for benchmark',
                    embench_run_dir.name)

    return pcount_paths

def add_results_to_db(benchmark_name, pcount_path, results_db):
    with pcount_path.open() as pcount_file:
        pcount_csv = csv.reader(pcount_file)

        for row in pcount_csv:
            count_name = row[0]
            count_num  = int(row[1])

            if count_name in results_db:
                results_db[count_name][benchmark_name] = count_num
            else:
                results_db[count_name] = {benchmark_name : count_num}

def write_out_db(results_db, benchmark_names, out_filename):
    out_file = open(out_filename, 'w')

    out_file.write(',')
    out_file.write(','.join(benchmark_names))
    out_file.write('\n')

    for count_name, results in results_db.items():
        out_file.write(count_name)

        for benchmark_name in benchmark_names:
            out_file.write(',')
            out_file.write(str(results_db[count_name][benchmark_name]))

        out_file.write('\n')


def main():
    arg_parser = argparse.ArgumentParser(description="""Gather performance counter
    results from embench run""")

    arg_parser.add_argument('embench_run_dir', help="""Directory containing the
    embench run""")

    arg_parser.add_argument('out_filename', help="File to output results to")

    args = arg_parser.parse_args()

    pcount_paths = get_pcount_paths(args.embench_run_dir)
    results_db = {}

    for benchmark_name, pcount_path in pcount_paths.items():
        add_results_to_db(benchmark_name, pcount_path, results_db)

    write_out_db(results_db, pcount_paths.keys(), args.out_filename)

if __name__ == "__main__":
    main()
