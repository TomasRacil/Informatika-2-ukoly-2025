import unittest
import os
from main import nacti_data, spocitej_prumer, prospel, zpracuj_vysledky, uloz_report

class TestEvidence(unittest.TestCase):
    
    def setUp(self):
        # Vytvoření dočasného testovacího souboru
        self.test_file_input = "test_data.txt"
        self.test_file_output = "test_report.txt"
        with open(self.test_file_input, "w", encoding="utf-8") as f:
            f.write("Jan Novak,1,2,1\n")
            f.write("Petr Spatny,5,5,4,5\n")
            f.write("Eva Prazdna,\n") # Student bez známek

    def tearDown(self):
        # Úklid po testech
        if os.path.exists(self.test_file_input):
            os.remove(self.test_file_input)
        if os.path.exists(self.test_file_output):
            os.remove(self.test_file_output)

    def test_spocitej_prumer(self):
        self.assertAlmostEqual(spocitej_prumer([1, 2, 3]), 2.0)
        self.assertAlmostEqual(spocitej_prumer([1, 1]), 1.0)
        self.assertAlmostEqual(spocitej_prumer([]), 0.0)

    def test_prospel(self):
        self.assertTrue(prospel(1.0))
        self.assertTrue(prospel(3.5))
        self.assertFalse(prospel(3.51))
        self.assertFalse(prospel(5.0))

    def test_nacti_data(self):
        data = nacti_data(self.test_file_input)
        self.assertEqual(len(data), 3)
        
        # Kontrola prvního studenta
        self.assertEqual(data[0]['jmeno'], "Jan Novak")
        self.assertEqual(data[0]['znamky'], [1, 2, 1])
        
        # Kontrola studenta bez známek (měl by mít prázdný list, ne chybu)
        self.assertEqual(data[2]['jmeno'], "Eva Prazdna")
        self.assertEqual(data[2]['znamky'], [])

    def test_zpracuj_vysledky(self):
        studenti = [
            {'jmeno': 'A', 'znamky': [1, 1]},
            {'jmeno': 'B', 'znamky': [5, 5]}
        ]
        vysledky = zpracuj_vysledky(studenti)
        
        self.assertEqual(vysledky['A']['prumer'], 1.0)
        self.assertTrue(vysledky['A']['prospel'])
        
        self.assertEqual(vysledky['B']['prumer'], 5.0)
        self.assertFalse(vysledky['B']['prospel'])

    def test_uloz_report(self):
        vysledky = {
            'Test Student': {'prumer': 1.5, 'prospel': True},
            'Test Fail': {'prumer': 4.0, 'prospel': False}
        }
        uloz_report(self.test_file_output, vysledky)
        
        self.assertTrue(os.path.exists(self.test_file_output))
        
        with open(self.test_file_output, "r", encoding="utf-8") as f:
            obsah = f.read()
            self.assertIn("Test Student: 1.5", obsah)
            self.assertIn("PROSPEL", obsah)
            self.assertIn("Test Fail: 4.0", obsah)
            self.assertIn("NEPROSPEL", obsah)

if __name__ == '__main__':
    unittest.main()