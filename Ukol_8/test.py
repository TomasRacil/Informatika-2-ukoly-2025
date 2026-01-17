import unittest
import os
import types
import inspect
from main import read_logs, process_line, analyze_logs

class TestLogAnalyzer(unittest.TestCase):
    
    def setUp(self):
        self.test_filename = "test_data.txt"
        self.output_filename = "test_output.txt"
        with open(self.test_filename, "w", encoding="utf-8") as f:
            f.write("[2024-01-01 10:00:00] INFO: Start - User: a@b.com\n")
            f.write("[2024-01-01 10:05:00] ERROR: Fail with spaces and dots - User: fail.user@sub.domain.co.uk\n")
            f.write("Bad line that should be skipped\n")
            f.write("[2024-01-01 10:10:00] ERROR: Crash - User: crash@b.com\n")

    def tearDown(self):
        if os.path.exists(self.test_filename):
            os.remove(self.test_filename)
        if os.path.exists(self.output_filename):
            os.remove(self.output_filename)

    def test_read_logs_is_generator(self):
        """Ověří, že read_logs vrací generátor, ne seznam."""
        gen = read_logs(self.test_filename)
        self.assertTrue(isinstance(gen, types.GeneratorType), "read_logs musí vracet generátor (yield)!")
        
        # Ověříme funkčnost
        lines = list(gen)
        self.assertEqual(len(lines), 4)

    def test_read_logs_missing_file(self):
        """Ověří, že neexistující soubor nezpůsobí pád aplikace."""
        try:
            gen = read_logs("non_existent_file_12345.txt")
            # Pokud funkce vrátí generátor i při chybě (např. prázdný), nebo None, nebo nic neyieldne
            if gen:
                result = list(gen)
                self.assertEqual(result, [], "Generátor by měl být prázdný pro neexistující soubor")
        except FileNotFoundError:
            self.fail("FileNotFoundError by měl být ošetřen uvnitř funkce!")

    def test_process_line_regex_complex(self):
        """Testuje složitější případy pro regex."""
        # Standard
        res = process_line("[2024-05-20 14:30:01] INFO: Msg - User: user@test.com")
        self.assertEqual(res['email'], 'user@test.com')

        # Complex email
        res = process_line("[2022-02-02 22:22:22] WARN: Something - User: first.last+tag@sub.example.org")
        self.assertEqual(res['email'], 'first.last+tag@sub.example.org')
        
        # Dots in message
        res = process_line("[2022-01-01 01:01:01] ERROR: Error 404... not found. - User: admin@local.host")
        self.assertEqual(res['message'], 'Error 404... not found.')

    def test_process_line_invalid(self):
        self.assertIsNone(process_line("Invalid line blob"))
        self.assertIsNone(process_line("[202020] INFO Only partial"))
        self.assertIsNone(process_line("INFO: Msg - User: no_timestamp"))

    def test_analyze_logs_logic(self):
        analyze_logs(self.test_filename, self.output_filename)
        
        self.assertTrue(os.path.exists(self.output_filename))
        
        with open(self.output_filename, "r", encoding="utf-8") as f:
            content = f.read()
            # Měly by tam být jen ty 2 ERRORY
            self.assertIn("fail.user@sub.domain.co.uk", content, "Chybí první error")
            self.assertIn("crash@b.com", content, "Chybí druhý error")
            
            # INFO by tam být nemělo
            self.assertNotIn("a@b.com", content, "INFO log by neměl být ve výstupu")

if __name__ == '__main__':
    unittest.main()
