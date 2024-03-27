#! /usr/bin/env python3
###############################################################################
# Use this file to tap along with a video for porting/testing purposes.
# NOTE: For now (probably forever?), this only reads on key down.
#       That is, it will not support holds.
# NOTE: This does not currently support unique buttons (EVENT_NUMBER).
###############################################################################

import curses
import datetime
from sys import argv

header = """
`
title:
bpm:
composer:
vocals:
original:
mapper:
offset:
metronome_offset:
`
""".strip()

if len(argv) > 1:
    path = argv[1].strip()
else:
    path = input("input filename to save to (/ seperator):\n").strip()

keys = {}

def main(screen):
    times = []

    screen.clear()
    screen.addstr("press any key when ready. Press enter to exit input mode.")
    screen.getkey()
    screen.clear()
    screen.addstr("Press enter to exit...")

    start_time = datetime.datetime.now()

    while True:
        key = screen.getkey()
        if key == "\n":
            break
        if key not in keys:
            keys[key] = len(keys)
        event = keys[key]

        times.append((datetime.datetime.now(), event))

    with open(path, 'w') as f:

        f.write(header + "\n")

        for (t, event_number) in times:
            delta:datetime.timedelta = t - start_time

            ss = delta.seconds
            us = delta.microseconds + ss * 1_000_000
            string = f"0 {us} {event_number}\n"
            f.write(string)

curses.wrapper(main)
