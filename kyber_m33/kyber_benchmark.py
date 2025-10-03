import serial
import csv
import sys
import argparse
import os
import re

# Patterns for the Kyber speed output
RE_MODULE = re.compile(r'^([A-Za-z0-9_ \-:/\.]+):\s*$')
RE_MEDIAN = re.compile(r'^median:\s*([0-9]+)')
RE_AVG    = re.compile(r'^average:\s*([0-9]+)')

def parse_args():
    p = argparse.ArgumentParser(description="Serial2CSV config")
    p.add_argument("-p", "--port", required=True, help="UART port, e.g. /dev/ttyACM0 or COM5")
    p.add_argument("-b", "--baud", type=int, default=1_000_000, help="Baud rate (default: 1000000)")
    p.add_argument("-o", "--outfile", type=str, default="output.csv", help="CSV output path")
    return p.parse_args()

def main():
    print("unparsed")
    args = parse_args()
    print("main")

    try:
        ser = serial.Serial(args.port, args.baud, timeout=1)
    except serial.SerialException as e:
        print(f"Failed to open {args.port}: {e}")
        sys.exit(2)

    # create parent directory if needed
    outdir = os.path.dirname(args.outfile)
    if outdir:
        os.makedirs(outdir, exist_ok=True)

    # open CSV and write header
    with open(args.outfile, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["Module", "Median", "Average"])
        f.flush()

        current = None  # holds {"Module": str, "Median": int?, "Average": int?}

        print(f"Logging {args.port}@{args.baud} → {args.outfile} (Ctrl+C to stop)")
        try:
            while True:
                line_bytes = ser.readline()
                if not line_bytes:
                    continue

                # decode UART bytes to text
                line = line_bytes.decode("utf-8", errors="replace").strip()
                if not line:
                    continue

                # match patterns
                m_mod = RE_MODULE.match(line)
                if m_mod:
                    # if previous block was partially filled, you can flush or ignore;
                    # here we only write complete rows, so we just start a new block.
                    current = {"Module": m_mod.group(1)}
                    continue

                m_med = RE_MEDIAN.match(line)
                if m_med:
                    if current is None:
                        current = {"Module": "(unknown)"}
                    current["Median"] = int(m_med.group(1))
                    continue

                m_avg = RE_AVG.match(line)
                if m_avg:
                    if current is None:
                        current = {"Module": "(unknown)"}
                    current["Average"] = int(m_avg.group(1))

                    # if we have a complete triple, write a CSV row
                    if "Module" in current and "Median" in current and "Average" in current:
                        writer.writerow([current["Module"], current["Median"], current["Average"]])
                        f.flush()
                        # print for quick feedback
                        print(f"Wrote: {current['Module']}, {current['Median']}, {current['Average']}")
                        current = None
                    continue

                # otherwise ignore miscellaneous lines (e.g., banners)
                # print(f"(ignored) {line}")  # uncomment for debugging

        except KeyboardInterrupt:
            print("\nStopped by user.")
        finally:
            ser.close()

if __name__ == "__main__":
    main()
