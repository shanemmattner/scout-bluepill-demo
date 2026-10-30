#!/usr/bin/env python3
"""Flash build/demo.bin, read `counter` for a few seconds, write counter.csv, plot counter.png.

Run: python3 read_counter.py --host omniprobe-b07d80.local --seconds 5 --hz 20
Needs: `make` done first, arm-none-eabi-nm on PATH, matplotlib, the `ohmic` Python binding.
Pattern sources: Scout sdk/host/py README (ohmic.call), https://matplotlib.org/stable/gallery/lines_bars_and_markers/simple_plot.html,
https://docs.python.org/3/library/csv.html, nm symbol lookup as in https://sourceware.org/binutils/docs/binutils/nm.html
"""
import argparse, csv, os, subprocess, time
import matplotlib.pyplot as plt
import ohmic

ap = argparse.ArgumentParser()
ap.add_argument("--host", default=os.environ.get("SCOUT_HOST"), help="probe name or IP")
ap.add_argument("--seconds", type=float, default=5)
ap.add_argument("--hz", type=float, default=5, help="max reads per second (one read takes ~150 ms)")
ap.add_argument("--elf", default="build/demo.elf")
ap.add_argument("--bin", default="build/demo.bin")
a = ap.parse_args()

# 1. Address of `counter` from the ELF symbol table.
nm = subprocess.run(["arm-none-eabi-nm", a.elf], capture_output=True, text=True, check=True).stdout
addr = int(next(l.split()[0] for l in nm.splitlines() if l.endswith(" counter")), 16)
print(f"counter at {addr:#010x}")

# 2. Flash (verified by CRC on the probe) and run.
h = {"host": a.host}
print(ohmic.call("flash_image", {**h, "path": a.bin, "flm": "stm32f103c8-flm.json"})["result"])
ohmic.call("reset", {**h, "mode": "run"})

# 3. Non-halting reads: the core keeps counting.
rows, t0 = [], time.time()
while (t := time.time() - t0) < a.seconds:
    words = ohmic.call("mem_read", {**h, "address": addr, "len": 4})["words"]
    rows.append((round(t, 3), int(words[0], 16)))
    time.sleep(max(0, 1 / a.hz - (time.time() - t0 - t)))

# 4. CSV, then plot.
with open("counter.csv", "w", newline="") as f:
    csv.writer(f).writerows([("t_s", "value"), *rows])
plt.plot(*zip(*rows))
plt.xlabel("seconds"); plt.ylabel("counter"); plt.title("counter, read over SWD")
plt.savefig("counter.png"); print(f"{len(rows)} samples -> counter.csv, counter.png")
plt.show()
