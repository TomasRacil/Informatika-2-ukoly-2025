
vyska:int = int(input("jak velky chces stromek"))
sirka:int = int(input("jak ma byt siroky"))
for i in range(vyska):
    print(" " * (vyska - i) + "*" * (i * 2 + 1))

print(" " * (vyska - sirka//2) + "|" * sirka)