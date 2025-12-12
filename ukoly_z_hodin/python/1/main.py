vyska:int = int(input("Zadej výšku stromu: "))
kmen_vyska:int = int(input("Zadej výšku kmene: "))
kmen_sirka:int = int(input("Zadej výšku kmene: "))

#for i in range(vyska):
    #radek:str = ""
    #for j in range(i):
    #    radek+= "*"
    # print(radek)
    #print("*"*(i+1))

for i in range(vyska):
    print(" " * (vyska - i - 1) + "*" * (2 * i + 1))

for i in range(kmen_vyska):
    print(" " * (vyska - kmen_sirka // 2 - 1) + "*" * kmen_sirka)