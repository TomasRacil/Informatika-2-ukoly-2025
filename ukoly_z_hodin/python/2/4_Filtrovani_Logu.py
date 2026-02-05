from pathlib import Path
import sys

LOG_PATH = Path(__file__).parent / "system.log"
OUT_PATH = Path(__file__).parent / "errors_only.txt"

def main():
    if not LOG_PATH.exists():
        print(f"Soubor nenalezen: {LOG_PATH}", file=sys.stderr)
        return 1

    with LOG_PATH.open("r", encoding="utf-8") as f:
        lines = f.readlines()

    errors = [line for line in lines if "ERROR" in line]

    with OUT_PATH.open("w", encoding="utf-8") as f:
        f.writelines(errors)

    print(f"Vyfiltrovano {len(errors)} radku s 'ERROR' do {OUT_PATH}")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())