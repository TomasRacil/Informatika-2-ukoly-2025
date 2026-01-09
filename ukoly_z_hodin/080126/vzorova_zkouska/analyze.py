from os.path import dirname, realpath, join
import re 

def read_logs(filename):
    with open(filename, "r", encoding="utf-8") as f:
        lines = f.readlines()

        for line in lines:
            yield line

current_dir = dirname(__file__)
logs = read_logs(join(current_dir, "server.log"))

class LogStat:
    stat_log_file_name = "stats_history.txt"

    def __init__(self):
        self.info = 0
        self.warning = 0
        self.error = 0

        self.n_info = 0
        self.n_warning = 0
        self.n_error = 0

        self.stat_log_file = join(current_dir, self.stat_log_file_name)

        try:
            with open(self.stat_log_file, "r", encoding="utf-8") as file:
                lines = file.readlines()

                for index, line in enumerate(lines):
                    if (index == 0):
                        self.info += int(line)
                    elif (index == 1):
                        self.warning += int(line)
                    elif (index == 2):
                        self.error += int(line)
        except Exception as e:
            print("FILE - doesn't yet exist!")
            
    def process_line(self, line):
        states = ["info", "warning", "error"]

        for state in states:
            state_match = re.search(state.upper(), line)

            if (state_match):
                match(state):
                    case "info":
                        self.n_info += 1
                    case "warning":
                        self.n_warning += 1
                    case "error":
                        self.n_error += 1
        
        with open(self.stat_log_file, "w", encoding="utf-8") as file:
            to_save = f"{self.info + self.n_info}\n{self.warning + self.n_warning}\n{self.error + self.n_error}"
            
            file.write(to_save)

    def __str__(self):
        string = f"""
        ------ Celkové statistiky ------
        -> Databáze
        INFO: {self.info}
        WARNING: {self.warning}
        ERROR: {self.error}

        -> Server
        INFO: {self.n_info}
        WARNING: {self.n_warning}
        ERROR: {self.n_error}
        --------------------------------
        """

        return string


new_logs = LogStat()

for log in logs:
    new_logs.process_line(log)

print(new_logs)