from os.path import dirname, join, realpath

soubor = join(dirname(realpath(__file__)), "day_5_data.txt")

def overlaps(intervals):
    if not intervals:
        return 0

    # Remove duplicates first
    intervals = [list(t) for t in {tuple(iv) for iv in intervals}]
    intervals.sort(key=lambda x: x[0])

    total = 0
    
    merged = [intervals[0]]
    for start, end in intervals[1:]:
        last_start, last_end = merged[-1]
        if start <= last_end + 1:
            merged[-1][1] = max(last_end, end)
        else:
            merged.append([start, end])
    
    print("merged", merged)

    print("intervals", len(merged))            
    total = sum(end - start + 1 for start, end in merged)
    return total

def main():
    with open(soubor, "r") as f:
        data = [v for v in f.read().split("x")]
        
        ranges = data[0].split("\n")
        numbers = [int(v) for v in data[1].split("\n") if v.strip() != ""]

        intervals = []
        
        for r in ranges:
            range_numbers = [v for v in r.split("-") if v.strip() != ""]

            if (len(range_numbers) != 2):
                continue

            start = int(range_numbers[0])
            end = int(range_numbers[1])

            for num in numbers:
                # print(f"checking num: {num} for range: {start}-{end}")
                if (num >= start and num <= end):
                    interval = [start, end]

                    if (interval not in intervals):
                        intervals.append(interval)

                    print(f"[PASSED] added num: {num} to fresh ids")
        
            
        total_fresh_ids = overlaps(intervals)
        print("FRESH IDS:", total_fresh_ids)
main()
