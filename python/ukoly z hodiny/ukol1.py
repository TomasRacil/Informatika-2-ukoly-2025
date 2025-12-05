seznam_cisel = []
sude = 0
liche = 0
prumer = 0
def pridani_cisla():
    cislo = input("zadej cislo, pro konec napis stop: ")
    seznam_cisel.append(int(cislo))  

while True:
    try:
        pridani_cisla()
    except:
        break
    
print(seznam_cisel)
seznam_cisel.sort()
print(seznam_cisel)

print(seznam_cisel[0] + seznam_cisel[-1])

for x in range(len(seznam_cisel)):
    
    if seznam_cisel[x] % 2 == 0:
        sude += 1
    else:
        liche +=1

print("sudych cisel je: ", int(sude))
print("lichych je: ", int(liche))

for p in range(len(seznam_cisel)):
    prumer = prumer + seznam_cisel[p]

print("prumerna hodnota je: ", prumer/len(seznam_cisel))