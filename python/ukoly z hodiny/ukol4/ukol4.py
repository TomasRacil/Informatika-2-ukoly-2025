file_path = "/workspaces/Informatika-2-ukoly-2025-Kolacek/python/ukoly z hodiny/ukol4/system.log"
file_to_write = "/workspaces/Informatika-2-ukoly-2025-Kolacek/python/ukoly z hodiny/ukol4/errors_only.txt"

with open(file_path, "r", encoding="UTF-8") as file:
    data = file.read()

with open(file_to_write, "w", encoding="UTF-8") as errors_only:
    for slovo in data.split():
        if slovo == "ERROR":
            errors_only.write("ERROR\n")
        else:
            errors_only.write("\n")


