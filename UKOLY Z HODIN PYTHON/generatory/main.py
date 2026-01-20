def countdown(n:int):
    for i in range(n, 0, -1):
        yield i

def suda_cisla():
    pass

if __name__ == "__main__":

    countd = countdown(5)

    print(next(countd))
    print(next(countd))
    print(next(countd))
    print(next(countd))
    print(next(countd))