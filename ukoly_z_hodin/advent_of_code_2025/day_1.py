from os.path import dirname, join, realpath

CURRENT_DIR = dirname(realpath(__file__))
INPUT_FILE = join(CURRENT_DIR, "day_1_data.txt")

zero_position = 0

def calculate_position(direction, distance, dial_number):
    global zero_position

    mod = distance % 100

    print("mod", mod)
    if (direction == "left"):
        dial_number -= mod
        
        if (dial_number < 0):
            dial_number = 100 + dial_number
    elif (direction == "right"):
         print("BEFORE:", dial_number)
         dial_number += mod 
         print("AFTER:", dial_number)

         if (dial_number > 99):
             dial_number = dial_number - 100

    print("dial", dial_number)
    if (dial_number == 0):
        zero_position += 1

    return dial_number

def main():
    dial_number = 50

    with open(INPUT_FILE, "r") as file:
        lines = file.readlines()

        for line in lines:
            direction = line[0] == "L" and "left" or "right"
            distance = int(line[1:].strip())

            dial_number = calculate_position(direction, distance, dial_number)
    
    print("Final zero position number:", zero_position)

main()