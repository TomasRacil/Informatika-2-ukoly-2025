import random

found = False

to_guess = random.randint(1, 100)

while not found:
    number = input("Enter a number between 1 and 100 for someone to guess: ")

    if (int(number) == to_guess):
        print("Congratulations! You guessed the number.")

        Found = True
    elif (int(number) < to_guess):
        print("Too low! Try again.")
    elif (int(number) > to_guess):
        print("Too high! Try again.")
