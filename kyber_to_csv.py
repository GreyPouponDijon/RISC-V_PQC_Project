# kyber_text_to_csv.py
import re, sys, csv, argparse

RE_MODULE = re.compile(r'^\s*([A-Za-z0-9_ \-:/\.]+):\s*$')
RE_MEDIAN = re.compile(r'^\s*median:\s*([0-9]+)')
RE_AVG    = re.compile(r'^\s*average:\s*([0-9]+)')

def parse_stream(lines):
    rows = []
    current = None
    for raw in lines:
        line = raw.strip()
        if not line:
            continue

        m = RE_MODULE.match(line)
        if m:
            # flush previous block if complete
            if current and 'Median' in current and 'Average' in current:
                rows.append(current)
            current = {'Module': m.group(1)}
            continue

        m2 = RE_MEDIAN.match(line)
        if m2:
            current = current or {'Module': '(unknown)'}
            current['Median'] = int(m2.group(1))
            continue

        m3 = RE_AVG.match(line)
        if m3:
            current = current or {'Module': '(unknown)'}
            current['Average'] = int(m3.group(1))
            # write row once we have both numbers
            if 'Median' in current and 'Average' in current:
                rows.append(current)
                current = None
            continue

    # if the last block was complete but not followed by a new module
    if current and 'Median' in current and 'Average' in current:
        rows.append(current)
    return rows

def main():
    ap = argparse.ArgumentParser(description="Convert Kyber speed test text to CSV")
    ap.add_argument("-i", "--input", default="-", help="Input file (default: stdin)")
    ap.add_argument("-o", "--output", default="metrics.csv", help="Output CSV path")
    args = ap.parse_args()

    # read lines
    if args.input == "-" or args.input == "/dev/stdin":
        lines = sys.stdin
    else:
        lines = open(args.input, "r", encoding="utf-8")

    rows = parse_stream(lines)
    if lines is not sys.stdin:
        lines.close()

    # write CSV
    with open(args.output, "w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["Module", "Median", "Average"])
        for r in rows:
            w.writerow([r.get("Module",""), r.get("Median",""), r.get("Average","")])

if __name__ == "__main__":
    main()

