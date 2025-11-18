vyska = int(input(print("jak ma byt strom vysoky")))
radek = vyska
vetev = 1

for i in range(vyska):
    print((radek-1)*"-",vetev*"*")
    vetev = vetev+1
    radek = radek - 1

print((vyska -3)*"-","||")