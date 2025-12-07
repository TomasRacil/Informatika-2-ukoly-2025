from os.path import dirname, join, realpath

soubor = join(dirname(realpath(__file__)), "day_6_data.txt")

def safe_get (l, idx, default):
  try:
    return l[idx]
  except IndexError:
    return default
  
def main():
    with open(soubor, "r") as f:
        data = f.read().splitlines()

        operators = [operator for operator in data[len(data) - 1].split(" ") if operator.strip() != ""]

        number_lines = []

        for num_line in data[0:len(data) - 1]:
            number_lines.append([int(num) for num in num_line.split(" ") if num.strip()])

        print(number_lines)

        result = 0
        index_results = {}

        for number_index in range(0, len(number_lines[0])):
            operator = operators[number_index]

            for _, line in enumerate(number_lines):
                for index, num in enumerate(line):
                    if index == number_index:
                        index_result = 0

                        try:
                            index_result = index_results[number_index]
                        except KeyError:
                            index_results[number_index] = 0

                        if operator == "+":
                            index_result += num
                        elif operator == "*":
                            if index_result == 0:
                                index_result = 1
                            index_result *= num
                        
                        index_results[number_index] = index_result

        for _, value in index_results.items():
            result += value
        print("Result:", result)

main()