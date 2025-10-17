#!/usr/bin/env python3
import re
import sys
import csv
import time
import signal
import argparse
from pathlib import Path
from typing import Optional, Dict

try:
    import serial
except ImportError:
    print("ERROR: pyserial is required. Install with: pip install pyserial", file=sys.stderr)
    sys.exit(1)

FIELD_PATTERNS = {
    "Cycle Count": [
        r'\bCycle\s*Count\s*[:=]\s*(\d+)',
        r'\bTotal\s*cycles\s*[:=]\s*(\d+)',
    ],
    "Keccak count": [
        r'\bkeccak_count\b\s*[:=]?\s*(\d+)',
        r'\bState\s*Permute\s*calls\b\s*[:=]?\s*(\d+)',
    ],
    "Cycles per keccak": [
        r'\baverage\s*:\s*(\d+)\s*cycles/ticks\b',
        r'\bavg\s*[:=]\s*(\d+)\s*cycles/ticks\b',
        r'\bper\s*call\s*[:=]\s*(\d+)\s*(?:cycles|ticks)\b',
    ],
}

FUNC_PATTERNS = [
    r'\bslh_keygen\b',
    r'\bslh_sign\b',
    r'\bslh_verify\b',
]

def detect_function(line: str) -> Optional[str]:
    for pat in FUNC_PATTERNS:
        if re.search(pat, line, re.IGNORECASE):
            return re.sub(r'\\b', '', pat).strip('\\b')
    return None

def extract_first_int(line: str, patterns) -> Optional[int]:
    for pat in patterns:
        m = re.search(pat, line, re.IGNORECASE)
        if m:
            try:
                return int(m.group(1))
            except Exception:
                pass
    return None

def compute_row(state: Dict[str, Optional[int]]) -> Optional[Dict[str, object]]:
    if state.get("Cycle Count") and state.get("Keccak count") and state.get("Cycles per keccak"):
        total = state["Cycle Count"]
        kc = state["Keccak count"]
        cpk = state["Cycles per keccak"]
        keccak_cycles = kc * cpk
        pct = (keccak_cycles / total) * 100.0 if total else None
        return {
            "Function": state.get("Function") or "unknown",
            "Cycle Count": total,
            "Keccak count": kc,
            "Cycles per keccak": cpk,
            "Total keccak cycles": keccak_cycles,
            "% cycles in keccak": round(pct, 4) if pct is not None else None,
            "Timestamp": time.strftime("%Y-%m-%d %H:%M:%S"),
        }
    return None

def write_header_if_needed(csv_path: Path, fieldnames):
    if not csv_path.exists() or csv_path.stat().st_size == 0:
        with csv_path.open("w", newline="") as f:
            w = csv.DictWriter(f, fieldnames=fieldnames)
            w.writeheader()

def append_row(csv_path: Path, row: Dict[str, object], fieldnames):
    with csv_path.open("a", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writerow(row)

def main(argv=None):
    ap = argparse.ArgumentParser(description="Read UART, parse PQC/Keccak metrics, stop on Ctrl+C.")
    ap.add_argument("--port", required=True, help="Serial port (e.g. /dev/ttyACM0 or COM5)")
    ap.add_argument("--baud", type=int, default=115200, help="Baud rate (default: 115200)")
    ap.add_argument("--csv", type=str, default="uart_keccak_log.csv", help="Output CSV path")
    ap.add_argument("--function", type=str, help="Function name (slh_keygen/slh_sign/slh_verify). If omitted, auto-detect from lines.")
    ap.add_argument("--flush-every", type=int, default=0, help="Force-close a run every N lines (0 = disabled)")
    ap.add_argument("--newline", type=str, default="\\n", help="UART line terminator to split on (default: \\n)")
    args = ap.parse_args(argv)

    out_csv = Path(args.csv).resolve()
    fieldnames = ["Timestamp","Function","Cycle Count","Keccak count","Cycles per keccak","Total keccak cycles","% cycles in keccak"]
    write_header_if_needed(out_csv, fieldnames)

    ser = serial.Serial(args.port, args.baud, timeout=0.1)
    print(f"[UART] Listening on {ser.port} @ {ser.baudrate}. Press Ctrl+C to stop.", flush=True)

    buf = ""
    state: Dict[str, Optional[int]] = {"Function": args.function}
    line_counter = 0

    try:
        while True:
            chunk = ser.read(4096).decode(errors="ignore")
            if chunk:
                buf += chunk
                while args.newline in buf:
                    line, buf = buf.split(args.newline, 1)
                    sline = line.strip()
                    if not sline:
                        continue

                    print(sline)
                    line_counter += 1

                    # function detection
                    if state.get("Function") is None:
                        fn = detect_function(sline)
                        if fn:
                            state["Function"] = fn

                    # field extraction
                    for field, patterns in FIELD_PATTERNS.items():
                        val = extract_first_int(sline, patterns)
                        if val is not None:
                            state[field] = val

                    # try to finalize a row
                    row = compute_row(state)
                    if row:
                        append_row(out_csv, row, fieldnames)
                        print(f"[Saved] {row}")
                        # reset for next run, keep same function unless you want to clear it
                        state = {"Function": state.get("Function")}

                    # optional forced flush (useful if the firmware interleaves prints)
                    if args.flush_every and (line_counter % args.flush_every == 0):
                        row = compute_row(state)
                        if row:
                            append_row(out_csv, row, fieldnames)
                            print(f"[Forced Save] {row}")
                        state = {"Function": state.get("Function")}
            else:
                time.sleep(0.02)
    except KeyboardInterrupt:
        print("\\n[Exit] Keyboard interrupt received. Attempting to finalize current run...")
        row = compute_row(state)
        if row:
            append_row(out_csv, row, fieldnames)
            print(f"[Saved on exit] {row}")
        print(f"[Done] CSV -> {out_csv}")
    finally:
        try:
            ser.close()
        except Exception:
            pass

if __name__ == "__main__":
    sys.exit(main())
