#! /usr/bin/env python3
bpm = 1/float(input("bpm?"))

while True:
    choice = input("quantize to [Q]uarter/[E]ight?").upper()
    if choice in "QE":
        break

print("Times:")
lines = []
while inp := input().strip():
    lines += inp.split("\n")

lines = [l if l[0].isnumeric() else " " for l in lines]
lines = [l.split()[0] for l in lines]
times = [int(l) for l in lines]

if choice == "Q":
    time_of_minimum = int(bpm * 60 * 1_000_000 * 1)
elif choice == "E":
    time_of_minimum = int(bpm * 60 * 1_000_000 * 2)
elif choice == "S":
    time_of_minimum = int(bpm * 60 * 1_000_000 * 4)

print(f"{time_of_minimum=}")

# Divide, convert to int, and the multiply back to take a floor of some sort
times =[int(t/time_of_minimum)*time_of_minimum for t in times]


print("Output:")
for time in times:
    time = str(time)
    print(time, '1')