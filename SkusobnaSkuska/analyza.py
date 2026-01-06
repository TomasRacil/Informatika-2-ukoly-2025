import re
import os
from os.path import join, dirname, realpath, exists

def read_input(file_name="server.log"):
    file_path = join(dirname(realpath(__file__)),"build", file_name)
    with open(file_path, "r", encoding="utf-8") as file:
        for line in file:
            yield line.strip()

class LogStat:
    HISTORY_FILE = "stats_history.txt"

    def __init__(self, history_file=None):
        self.HISTORY_FILE = history_file or "stats_history.txt"
        self.stats = {
            "Database": {"INFO": 0, "WARNING": 0, "ERROR": 0},
            "Server":   {"INFO": 0, "WARNING": 0, "ERROR": 0},
            "System":   {"INFO": 0, "WARNING": 0, "ERROR": 0},
        }

        self.data = self.stats #len kvoli funkcii testov
        self._load_history()

        self.pattern = re.compile(
            r"\[\d+\]\s+(INFO|WARNING|ERROR):\s+(\w+)\s+-\s+(.+)"
        )

    def _load_history(self):
        file_path = join(dirname(realpath(__file__)), self.HISTORY_FILE)

        if not exists(file_path):
            return

        with open(file_path, "r", encoding="utf-8") as f:
            for line in f:
                parts = line.strip().split()
                if len(parts) != 3:
                    continue

                obj, level, count = parts

                if obj in self.stats and level in self.stats[obj]:
                    self.stats[obj][level] = int(count)


    def save(self):
        file_path = join(dirname(realpath(__file__)), self.HISTORY_FILE)

        with open(file_path, "w", encoding="utf-8") as f:
            for obj, levels in self.stats.items():
                for level, count in levels.items():
                    f.write(f"{obj} {level} {count}\n")

    def process_line(self, line):
        match = self.pattern.match(line)
        if not match:
            return

        level, obj, _ = match.groups()

        if obj in self.stats and level in self.stats[obj]:
            self.stats[obj][level] += 1

    def __str__(self):
        result = ["\n=== Agregovane statistiky historie included==="]
        for obj, levels in self.stats.items():
            result.append(f"\n{obj}:")
            for level, count in levels.items():
                result.append(f"  {level}: {count}")
        return "\n".join(result)


if __name__ == "__main__":
    stats = LogStat()  
    for line in read_input("server.log"):
        stats.process_line(line)
    print(stats)
    stats.save()
