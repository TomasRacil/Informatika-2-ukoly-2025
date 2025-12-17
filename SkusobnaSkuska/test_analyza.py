import unittest
import os
from analyza import read_logs, LogStat

TEST_LOG = "test_server.log"
HISTORY = "stats_history.txt"

class TestAnalyza(unittest.TestCase):

    def setUp(self):
        for f in [TEST_LOG, HISTORY]:
            if os.path.exists(f):
                os.remove(f)

        with open(TEST_LOG, "w", encoding="utf-8") as f:
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

    # ---------- Tests ----------

    def test_read_logs_generator(self):
        gen = read_logs(TEST_LOG)
        self.assertTrue(hasattr(gen, "__iter__"))
        self.assertTrue(hasattr(gen, "__next__"))

    def test_logstat_counts_all_levels(self):
        stats = LogStat()
        for line in read_logs(TEST_LOG):
            stats.process_line(line)

        self.assertEqual(stats.data["Server"]["ERROR"], 2)
        self.assertEqual(stats.data["Server"]["WARNING"], 2)
        self.assertEqual(stats.data["Server"]["INFO"], 0)

        self.assertEqual(stats.data["System"]["INFO"], 2)
        self.assertEqual(stats.data["System"]["WARNING"], 1)
        self.assertEqual(stats.data["System"]["ERROR"], 0)

        self.assertEqual(stats.data["Database"]["ERROR"], 2)
        self.assertEqual(stats.data["Database"]["INFO"], 1)
        self.assertEqual(stats.data["Database"]["WARNING"], 0)

    def test_logstat_persistence(self):
        stats = LogStat()
        for line in read_logs(TEST_LOG):
            stats.process_line(line)
        stats.save()

        stats2 = LogStat()
        self.assertEqual(stats2.data["Server"]["ERROR"], 2)
        self.assertEqual(stats2.data["Database"]["INFO"], 1)

    def test_empty_file(self):
        with open(TEST_LOG, "w"):
            pass
        stats = LogStat()
        for line in read_logs(TEST_LOG):
            stats.process_line(line)
        for obj in stats.data:
            for level in stats.data[obj]:
                self.assertEqual(stats.data[obj][level], 0)

    def test_invalid_lines_ignored(self):
        with open(TEST_LOG, "a") as f:
            f.write("invalid line\n")
            f.write("1234 RANDOM TEXT\n")
        stats = LogStat()
        for line in read_logs(TEST_LOG):
            stats.process_line(line)
        self.assertEqual(stats.data["Server"]["ERROR"], 2)

if __name__ == "__main__":
    unittest.main()
