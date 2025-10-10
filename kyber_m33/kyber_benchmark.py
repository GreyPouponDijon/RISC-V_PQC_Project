import serial
import csv
import sys
import argparse
import os
import re

# Accept module lines with or without a trailing colon
RE_MODULE = re.compile(r'^([A-Za-z0-9_ \-:/\.]+?)(?:\s*:)?\s*$')
RE_MEDIAN = re.compile(r'^median:\s*([0-9]+)', re.IGNORECASE)
RE_AVG    = re.compile(r'^average:\s*([0-9]+)', re.IGNORECASE)

def parse_args():
    p = argparse.ArgumentParser(description="Serial2CSV config")
    p.add_argument("-p", "--port", required=True, help="UART port, e.g. /dev/ttyACM0 or COM5")
    p.add_argument("-b", "--baud", type=int, default=1_000_000, help="Baud rate (default: 1000000)")
    p.add_argument("-o", "--outfile", type=str, default="output.csv", help="CSV output path")
    return p.parse_args()

def main():
    args = parse_args()

    try:
        ser = serial.Serial(args.port, args.baud, timeout=1)
    except serial.SerialException as e:
        print(f"Failed to open {args.port}: {e}")
        sys.exit(2)

    outdir = os.path.dirname(args.outfile)
    if outdir:
        os.makedirs(outdir, exist_ok=True)

    with open(args.outfile, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["Module", "Median", "Average"])
        f.flush()

        current = None  # {"Module": str, "Median": int?, "Average": int?}

        print(f"Logging {args.port}@{args.baud} → {args.outfile} (Ctrl+C to stop)")
        try:
            while True:
                line_bytes = ser.readline()
                if not line_bytes:
                    continue

                line = line_bytes.decode("utf-8", errors="replace").strip()
                if not line:
                    continue

                # average first? (common in your 'State Permute calls' case)
                m_avg = RE_AVG.match(line)
                if m_avg:
                    if current is None:
                        # If we see an average without having seen a module, bucket it under unknown
                        current = {"Module": "(unknown)"}
                    current["Average"] = int(m_avg.group(1))

                    # If we already have a module name, write immediately even if median is missing
                    if "Module" in current:
                        writer.writerow([
                            current.get("Module", "(unknown)"),
                            current.get("Median", ""),
                            current.get("Average", ""),
                        ])
                        f.flush()
                        print(f"Wrote: {current.get('Module','(unknown)')}, {current.get('Median','')}, {current.get('Average','')}")
                        current = None
                    continue

                # median line (optional)
                m_med = RE_MEDIAN.match(line)
                if m_med:
                    if current is None:
                        current = {"Module": "(unknown)"}
                    current["Median"] = int(m_med.group(1))
                    continue

                # module header line (with or without colon)
                m_mod = RE_MODULE.match(line)
                if m_mod:
                    name = m_mod.group(1).strip()
                    # Heuristic: ignore obviously empty/noise matches
                    if name:
                        current = {"Module": name}
                    continue

                # else: ignore miscellaneous lines

        except KeyboardInterrupt:
            print("\nStopped by user.")
        finally:
            ser.close()

if __name__ == "__main__":
    main()

