from os.path import dirname, join, realpath

soubor = join(dirname(realpath(__file__)), "day_5_data.txt")

def overlaps(intervals):
    """Part 1: Union of all fresh ranges (total coverage)"""
    if not intervals:
        return 0
    
    # Use tuples throughout to avoid mutability issues
    intervals = sorted({tuple(iv) for iv in intervals}, key=lambda x: x[0])
    if not intervals:
        return 0
    
    merged = [list(intervals[0])]
    for current in intervals[1:]:
        last_start, last_end = merged[-1]
        if current[0] <= last_end + 1:
            merged[-1][1] = max(last_end, current[1])
        else:
            merged.append(list(current))  # Convert tuple to list for mutability
    
    total = sum(end - start + 1 for start, end in merged)
    return total

def count_fresh_ids(ranges, numbers):
    """Part 2: Count numbers that fall in ANY fresh range"""
    if not ranges or not numbers:
        return 0
    
    # Convert all ranges to tuples for consistent handling
    range_tuples = [tuple(r) for r in ranges]
    
    # Parse numbers safely
    valid_numbers = []
    for num_str in numbers:
        try:
            num = int(num_str)
            valid_numbers.append(num)
        except ValueError:
            continue
    
    fresh_count = 0
    for num in valid_numbers:
        for start, end in range_tuples:
            if start <= num <= end:
                fresh_count += 1
                break  # Found match, move to next number
    
    return fresh_count

def main():
    try:
        with open(soubor, "r") as f:
            content = f.read().strip()
            data = content.split("x")
            
            if len(data) < 2:
                print("Invalid file format: missing data sections")
                return
            
            # Parse ranges section (first part before "x")
            ranges_str = [line.strip() for line in data[0].strip().split("\n") if line.strip()]
            # Parse numbers section (second part after "x")  
            numbers_str = [line.strip() for line in data[1].strip().split("\n") if line.strip()]
            
            print(f"Parsed {len(ranges_str)} range lines, {len(numbers_str)} number lines")
            
            # Parse ranges robustly
            ranges = []
            for r in ranges_str:
                parts = [v.strip() for v in r.split("-") if v.strip()]
                if len(parts) == 2:
                    try:
                        start = int(parts[0])
                        end = int(parts[1])
                        if start <= end:
                            ranges.append([start, end])
                    except ValueError:
                        print(f"Skipping invalid range: {r}")
                        continue
            
            if not ranges:
                print("No valid ranges found")
                return
                
            print(f"Valid ranges: {len(ranges)}")
            
            # PART 1: Total coverage of fresh ranges
            total_fresh_coverage = overlaps(ranges)
            print("PART 1 - FRESH IDS (coverage):", total_fresh_coverage)
            
            # PART 2: Count available IDs that are fresh
            fresh_available_ids = count_fresh_ids(ranges, numbers_str)
            print("PART 2 - FRESH AVAILABLE IDS:", fresh_available_ids)
            
    except FileNotFoundError:
        print(f"File {soubor} not found. Create it with format: ranges\nx\nnumbers")
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    main()
