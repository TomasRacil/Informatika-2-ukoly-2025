from os.path import dirname, join, realpath

soubor = join(dirname(realpath(__file__)), "test.txt")

def main():
    with open(soubor, "r") as f:
        data = f.read().splitlines()

        operators = data[len(data) - 1]

        for index, number in enumerate("".join(data[0:len(data) - 2]).split(" ")):
            print(f"Operator {operators[index]} applied to number {number}")

main()