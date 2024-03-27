#! /usr/bin/env python3
import argparse

parser = argparse.ArgumentParser(prog="quantize.py", description="Quantize beatmap files")
parser.add_argument('in_filename')
parser.add_argument('out_filename')

parser.add_argument('--bpm', action='store', type=float, required=True)
parser.add_argument('--division', action='store', default='q', choices=['q', 'e', 's'], type=str, required=True)
parser.add_argument('--index', action='store', type=int, required=True)
parser.add_argument('--start_on', action='store', type=int)
parser.add_argument('--baseball', action='store_true')

args = parser.parse_args()
bpm = 1/args.bpm

if args.division == "q":
    time_of_minimum = int(bpm * 60 * 1_000_000 * 1)
elif args.division == "e":
    time_of_minimum = int(bpm * 60 * 1_000_000 * 2)
elif args.division == "s":
    time_of_minimum = int(bpm * 60 * 1_000_000 * 4)

header = []
data = []
with open(args.in_filename) as f:
    header_start = False

    # Read header
    while (line := f.readline().strip()):
        if not header_start:
             if line.startswith('`'):
                header_start = True
        
        else:
            if line.startswith('`'):
                break
            else:
                header.append(line + "\n")

    # Read data
    while (line := f.readline().strip()):
        data.append(line)

delta = 0
if args.start_on:
    t0 = int(data[0].split()[args.index])
    t0 = time_of_minimum * int(t0/time_of_minimum)
    delta = args.start_on - t0

# Do processing and output
with open(args.out_filename, 'w') as f:
    f.write('`\n')
    f.writelines(header)
    f.write('`\n')

    for line in data:
        components = line.split()
        t = int(components[args.index])
        components[args.index] = time_of_minimum * int(t/time_of_minimum)
        components[args.index] += delta

        if args.baseball:
            dt = time_of_minimum if components[-1] == '0' else time_of_minimum*2
            launch = [
                str(1),
                str(components[1] - dt),
                str(components[-1]), "\n"
            ]
            f.write(" ".join(launch))

        for c in components:
            f.write(str(c))
            f.write(" ")
        f.write("\n")