from os.path import dirname, join, realpath

soubor = join(dirname(realpath(__file__)), "day_5_data.txt")

def main():
    with open(soubor, "r") as f:
        data = [v for v in f.read().split("x")]
        
        ranges = data[0].split("\n")
        numbers = [int(v) for v in data[1].split("\n") if v.strip() != ""]

        fresh_ids = []
        
        for r in ranges:
            range_numbers = [v for v in r.split("-") if v.strip() != ""]

            if (len(range_numbers) != 2):
                continue

            start = int(range_numbers[0])
            end = int(range_numbers[1])

            for num in numbers:
                if (num >= start and num <= end):
                    if num not in fresh_ids:
                        fresh_ids.append(num)
                        print(f"[PASSED] added num: {num} to fresh ids")

        print("FRESH IDS:", fresh_ids, len(fresh_ids))
main()
