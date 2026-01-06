data = []

with open("/workspaces/Informatika-2-ukoly-2025-Kolacek/Ukol_6/studenti.txt", "r") as file:
    for line in file:

        radek = line.strip().split(",")
        
        jmeno = radek[0]
        znamky = [int(z) for z in radek[1:] if z.strip() != ""]

        data.append({"jemno": jmeno,
                     "znamky": znamky})
        
print(data)