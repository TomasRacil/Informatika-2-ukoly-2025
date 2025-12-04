numbers = []

def analyze_numbers(nums):
    if (len(nums) > 0):
        min_max_num_sum = max(nums) + min(nums)
        odd_count = sum(1 for n in nums if n % 2 != 0)
        even_count = sum(1 for n in nums if n % 2 == 0)
        average = sum(nums) / len(nums)

        print(f"Sum of min and max: {min_max_num_sum}")
        print(f"Count of odd numbers: {odd_count}")
        print(f"Count of even numbers: {even_count}")
        print(f"Average: {average}")
    else:
        print("Missing numbers")

def main():
    while True:
        my_input = input("Enter a number (or 'stop' to quit): ")

        if my_input.lower() == 'stop':
            print("Exiting the program.")

            analyze_numbers(numbers)
            break

        try:
            number = float(my_input)

            numbers.append(number)
            
        except ValueError:
            print("Invalid input. Please enter a valid number.")
            continue
    
main()