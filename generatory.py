def pocitadlo(n:int): 
    for i in range(n, 0, -1):
        yield i

def nekonecne(n:int):
    i = 0
    while True:
        yield i
        i += 1
        
countd = (i for i in range(5, 0, -1))
for i in range(5):
   print(next(countd))