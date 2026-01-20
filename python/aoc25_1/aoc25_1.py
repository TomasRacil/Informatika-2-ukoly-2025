zacatek = 50
counter = 0
with open("python/ukoly z hodiny/aoc25_1/data.txt") as f:
    for radek in f:
        aktual_radek = radek.strip()


        
        if aktual_radek[0] == "L":
            zacatek -= int(aktual_radek[1:]) 
            if zacatek < 0:
                zacatek %= 100
        if aktual_radek[0] == "R":
            zacatek += int(aktual_radek[1:])
            if zacatek >= 100:
                zacatek %= 100
        if zacatek == 0:
            counter += 1
        #print(zacatek)
print("toto je odpoved: ",counter)