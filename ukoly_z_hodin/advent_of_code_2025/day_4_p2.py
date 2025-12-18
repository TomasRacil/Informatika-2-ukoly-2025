from os.path import dirname, join, realpath

soubor = join(dirname(realpath(__file__)), "day_4_data.txt")

def safe_get (l, idx, default):
  try:
    if (idx <= -1):
       return -1
    
    return l[idx]
  except IndexError:
    return default
  
def main():
    with open(soubor, "r") as f:
        data = [s for s in list(f.read()) if s != "\n"]

        copy_data = data.copy()

        total_paper_rolls = 0
        chars_per_line = 140

        while (True):
            paper_rolls = 0

            for index, char in enumerate(data):
                left_char = safe_get(data, index - 1, -1)
                right_char = safe_get(data, index + 1, -1)

                top_char = safe_get(data, index - chars_per_line, -1)
                top_left_char = safe_get(data, index - (chars_per_line + 1), -1)
                top_right_char = safe_get(data, index - (chars_per_line - 1), -1)

                low_char = safe_get(data, index + chars_per_line, -1)
                low_left_char = safe_get(data, index + (chars_per_line - 1), -1)
                low_right_char = safe_get(data, index + (chars_per_line + 1), -1)

                if (index % chars_per_line == 0): # left border
                    # print(f"[{index}-{char}] left border")
                    left_char = -1
                    top_left_char = -1
                    low_left_char = -1

                elif (index % chars_per_line == chars_per_line - 1): # right border
                    # print(f"[{index}-{char}] right border")
                    right_char = -1
                    top_right_char = -1
                    low_right_char = -1

                paper_roll_list = [
                    left_char, right_char,
                    top_char, top_left_char, top_right_char,
                    low_char, low_left_char, low_right_char
                                ]
                
                # print(paper_roll_list, "CH:", char, "index", index)
                paper_rolls += 1 if char == "@" and len([p for p in paper_roll_list if p == "@"]) < 4 else 0
                total_paper_rolls += 1 if char == "@" and len([p for p in paper_roll_list if p == "@"]) < 4 else 0
                data[index] = "." if char == "@" and len([p for p in paper_roll_list if p == "@"]) < 4 else char

                # print("paper rolls left: ", paper_rolls)

            if paper_rolls == 0:
                break
        # for i in range(0, len(copy_data), 10):
        #     print("".join(copy_data[i:i+10]))
        print(total_paper_rolls)

main()