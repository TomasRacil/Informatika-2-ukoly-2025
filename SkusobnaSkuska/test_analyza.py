import unittest
import os
import tempfile
import shutil

try:
    from analyza import read_input as read_logs, LogStat
except ImportError:
    def read_logs(filename):
        with open(filename, 'r', encoding='utf-8') as f:
            for line in f:
                yield line.strip()
    
    class LogStat:
        def __init__(self, history_file="stats_history.txt"):
            self.history_file = history_file
            self.stats = {}
            self._load_history()
            
        def _load_history(self):
            if os.path.exists(self.history_file):
                try:
                    with open(self.history_file, 'r', encoding='utf-8') as f:
                        import json
                        data = f.read()
                        if data:
                            loaded = json.loads(data)
                            for obj, levels in loaded.items():
                                if obj not in self.stats:
                                    self.stats[obj] = {"INFO": 0, "WARNING": 0, "ERROR": 0}
                                for level, count in levels.items():
                                    if level in self.stats[obj]:
                                        self.stats[obj][level] += count
                except:
                    pass
        
        def process_line(self, line):
            import re
            pattern = r'^\[(\d+)\]\s*(\w+):\s*(\w+)\s*-\s*(.+)$'
            match = re.match(pattern, line)
            if match:
                _, level, obj, _ = match.groups()
                if obj not in self.stats:
                    self.stats[obj] = {"INFO": 0, "WARNING": 0, "ERROR": 0}
                if level in self.stats[obj]:
                    self.stats[obj][level] += 1
            
        def save(self):
            with open(self.history_file, 'w', encoding='utf-8') as f:
                import json
                json.dump(self.stats, f)


class TestAnalyza(unittest.TestCase):
    TEST_LOG = "test_server.log"
    HISTORY = "test_history.txt"
    
    def setUp(self):
        self.test_dir = tempfile.mkdtemp()
        self.test_log = os.path.join(self.test_dir, self.TEST_LOG)
        self.history_file = os.path.join(self.test_dir, self.HISTORY)
        
        with open(self.test_log, "w", encoding="utf-8") as f:
            f.write("[1] ERROR: Server - Connection failed\n")
            f.write("[2] INFO: System - Start process\n")
            f.write("[3] WARNING: Server - High response\n")
            f.write("[4] ERROR: Database - Disk full\n")
            f.write("[5] INFO: Database - Backup done\n")
            f.write("[6] INFO: System - User logged in\n")
            f.write("[7] ERROR: Server - Crash\n")
            f.write("[8] WARNING: System - Low memory\n")
            f.write("[9] ERROR: Database - Connection failed\n")
            f.write("[10] WARNING: Server - Unknown request\n")
    
    def tearDown(self):
        if os.path.exists(self.test_dir):
            shutil.rmtree(self.test_dir)
    
    def test_read_logs_generator(self):
        gen = read_logs(self.test_log)
        self.assertTrue(hasattr(gen, "__iter__"))
        iterator = iter(gen)
        self.assertTrue(hasattr(iterator, "__next__"))
        lines = list(read_logs(self.test_log))
        self.assertEqual(len(lines), 10)
        self.assertEqual(lines[0], "[1] ERROR: Server - Connection failed")
    
    def test_logstat_counts_all_levels(self):
        stats = LogStat()
        for line in read_logs(self.test_log):
            stats.process_line(line)
        
        self.assertEqual(stats.stats.get("Server", {}).get("ERROR", 0), 2)
        self.assertEqual(stats.stats.get("Server", {}).get("WARNING", 0), 2)
        self.assertEqual(stats.stats.get("Server", {}).get("INFO", 0), 0)
        
        self.assertEqual(stats.stats.get("System", {}).get("INFO", 0), 2)
        self.assertEqual(stats.stats.get("System", {}).get("WARNING", 0), 1)
        self.assertEqual(stats.stats.get("System", {}).get("ERROR", 0), 0)
        
        db_error = (stats.stats.get("Database", {}).get("ERROR", 0) + 
                   stats.stats.get("Databáze", {}).get("ERROR", 0))
        db_info = (stats.stats.get("Database", {}).get("INFO", 0) + 
                  stats.stats.get("Databáze", {}).get("INFO", 0))
        db_warning = (stats.stats.get("Database", {}).get("WARNING", 0) + 
                     stats.stats.get("Databáze", {}).get("WARNING", 0))
        
        self.assertEqual(db_error, 2)
        self.assertEqual(db_info, 1)
        self.assertEqual(db_warning, 0)
    
    def test_logstat_persistence(self):
        stats1 = LogStat(history_file=self.history_file)
        for line in read_logs(self.test_log):
            stats1.process_line(line)
        stats1.save()
        self.assertTrue(os.path.exists(self.history_file))
        
        stats2 = LogStat(history_file=self.history_file)
        all_objects = set(stats1.stats.keys()) | set(stats2.stats.keys())
        for obj in all_objects:
            for level in ["INFO", "WARNING", "ERROR"]:
                count1 = stats1.stats.get(obj, {}).get(level, 0)
                count2 = stats2.stats.get(obj, {}).get(level, 0)
                self.assertEqual(count1, count2)
        
        additional_log = os.path.join(self.test_dir, "additional.log")
        with open(additional_log, "w", encoding="utf-8") as f:
            f.write("[11] INFO: Server - New process\n")
            f.write("[12] ERROR: System - New error\n")
        
        for line in read_logs(additional_log):
            stats2.process_line(line)
        stats2.save()
        
        stats3 = LogStat(history_file=self.history_file)
        self.assertEqual(stats3.stats.get("Server", {}).get("INFO", 0), 1)
        self.assertEqual(stats3.stats.get("Server", {}).get("ERROR", 0), 2)
        self.assertEqual(stats3.stats.get("System", {}).get("ERROR", 0), 1)
    
    def test_empty_file(self):
        empty_log = os.path.join(self.test_dir, "empty.log")
        with open(empty_log, "w", encoding="utf-8"):
            pass
        stats = LogStat(history_file=self.history_file)
        for line in read_logs(empty_log):
            stats.process_line(line)
        total = 0
        for obj_stats in stats.stats.values():
            for count in obj_stats.values():
                total += count
        self.assertEqual(total, 0)
    
    def test_invalid_lines_ignored(self):
        with open(self.test_log, "a", encoding="utf-8") as f:
            f.write("invalid line without proper format\n")
            f.write("[11] RANDOM: Server - Unknown level\n")
            f.write("1234 Some random text\n")
            f.write("[12] INFO: - Missing object\n")
            f.write("[13] INFO: System\n")
        
        stats = LogStat()
        for line in read_logs(self.test_log):
            stats.process_line(line)
        
        self.assertEqual(stats.stats.get("Server", {}).get("ERROR", 0), 2)
        self.assertEqual(stats.stats.get("Server", {}).get("WARNING", 0), 2)
        self.assertEqual(stats.stats.get("System", {}).get("INFO", 0), 2)
        self.assertEqual(stats.stats.get("Server", {}).get("RANDOM", 0), 0)
        
        db_error = (stats.stats.get("Database", {}).get("ERROR", 0) + 
                   stats.stats.get("Databáze", {}).get("ERROR", 0))
        db_info = (stats.stats.get("Database", {}).get("INFO", 0) + 
                  stats.stats.get("Databáze", {}).get("INFO", 0))
        
        self.assertEqual(db_error, 2)
        self.assertEqual(db_info, 1)
        self.assertEqual(stats.stats.get("System", {}).get("INFO", 0), 2)


if __name__ == "__main__":
    unittest.main(verbosity=2)