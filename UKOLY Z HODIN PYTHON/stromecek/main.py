vyska=int(input("Zadej výšku stromku: "))
sirka=int(input("Zadej šířku stromku: "))
vyska_kmen=int(input("Zadej výšku kmene: "))
sirka_kmen=int(input("Zadej šířku kmene: "))

for i in range(vyska):
    for j in range(vyska - i - 1):
        print(" ", end="")
    for k in range(2 * i + 1):
        print("*", end="")
    print()
   
for _ in range(vyska_kmen):
    print(" "*((vyska-sirka_kmen//2)-1) +"#"*sirka_kmen)