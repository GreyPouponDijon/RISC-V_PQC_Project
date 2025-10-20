#!/usr/bin/env python3
import serial
import time
import argparse
from pathlib import Path

def main():
    parser = argparse.ArgumentParser(description="Basic UART line logger (Ctrl+C to stop).")
    parser.add_argument("--port", required=True, help="Serial port (e.g. /dev/ttyACM0 or COM5)")
    parser.add_argument("--baud", type=int, default=1000000, help="Baud rate (default: 1000000)")
    parser.add_argument("--out", default="uart_log.txt", help="Output text file (default: uart_log.txt)")
    parser.add_argument("--newline", default="\n", help="Line ending (default: \\n)")
    args = parser.parse_args()

    outfile = Path(args.out).resolve()
    print(f"[INFO] Opening {args.port} @ {args.baud} baud...")
    print(f"[INFO] Writing log to: {outfile}")
    print("[INFO] Press Ctrl+C to stop.\n")

    ser = serial.Serial(args.port, args.baud, timeout=0.1)

    buf = ""
    try:
        with outfile.open("a", encoding="utf-8") as f:
            while True:
                data = ser.read(4096).decode(errors="ignore")
                if data:
                    buf += data
                    while args.newline in buf:
                        line, buf = buf.split(args.newline, 1)
                        line = line.strip()
                        if line:
                            print(f"[READ] {line}")
                            f.write(line + "\n")
                            f.flush()
                            print(f"[WRITE] wrote to {outfile}")
                else:
                    time.sleep(0.05)
    except KeyboardInterrupt:
        print("\n[EXIT] Keyboard interrupt received, stopping logger.")
    finally:
        ser.close()
        print("[INFO] Serial port closed.")

if __name__ == "__main__":
    main()

