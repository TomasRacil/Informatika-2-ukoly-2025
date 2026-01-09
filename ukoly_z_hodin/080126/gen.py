num = 100

generator = (n for n in range(num, 0, -1))

cd = [next(generator) for _ in range(num, 0, -1)]

print(*cd)

# we can also do it using yield number