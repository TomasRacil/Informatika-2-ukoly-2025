studenti = []

def pridej_studenta(jmeno, znamky):
    if not isinstance(jmeno, str) or not isinstance(znamky, list):
        raise ValueError("Neplatný formát vstupu.")
    
    studenti.append({"jmeno": jmeno, "znamky": znamky})

def nejlepsi_student():
    if not studenti:
        return None
    
    nejlepsi_student = None
    nejnizsi_prumer = 0

    for student in studenti:
        prumer = sum(student["znamky"]) / len(student["znamky"])
        if nejlepsi_student is None or prumer < nejnizsi_prumer:
            nejlepsi_student = student
            nejnizsi_prumer = prumer

    return nejlepsi_student

def main():
    while True:
        jmeno = input("Zadejte jméno studenta (nebo 'stop' pro ukončení): ")

        if jmeno.lower() == 'stop':
            best_student = nejlepsi_student()

            if best_student:
                print("Nejlepsi student je:", best_student)
            break

        znamky_input = input("Zadejte známky studenta oddělené čárkou: ")

        try:
            znamky = [float(z.strip()) for z in znamky_input.split(',')]

            pridej_studenta(jmeno, znamky)
        except ValueError:
            print("Neplatný formát známek. Zkuste to znovu.")
            continue

main()