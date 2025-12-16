studenti = {}

while True:
    jmeno = input("zadej jmeno, nebo konec pro ukonceni: ")
    if jmeno == "konec":
        break
    else:
        znamky_str = input("zadej znamky oddelene mezerou: ")
        znamky_int = [int(x) for x in znamky_str.split()]
        studenti[jmeno] = znamky_int
        print("tenhle hotov")

nejlepsi_student = min(studenti, key=lambda j: sum(studenti[j]) / len(studenti[j]))
print("Nejlepší student je:", nejlepsi_student, "s průměrem:", sum(studenti[nejlepsi_student]) / len(studenti[nejlepsi_student]))

