from os.path import join, realpath, dirname

path = join(dirname(realpath(__file__)), "system.log")

with open(path, "w", encoding="utf-8") as new_file:
    new_file.write(
        "INFO: something\n"
        "ERROR: missing a ..\n"
        "WARNING: be careful!\n"
        "ERROR: file not found\n"
        "WARNING: low disk space\n"
    )

def main():
    with open(path, "r", encoding="utf-8") as log_file:
         error_log_path = join(dirname(realpath(__file__)), "errors_only.txt")
         with open(error_log_path, "w", encoding="utf-8") as error_file:
            for line in log_file:
                if line.startswith("ERROR"):
                    error_file.write(line.strip() + "\n")

main()