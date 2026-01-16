import unittest
import os
import json
import sys
import io
from models import Product
from storage import Storage
from main import InventoryManager

class TestProduct(unittest.TestCase):
    def test_properties_enforced(self):
        """Ověří, že name, price a quantity jsou properties, ne obyčejné atributy."""
        self.assertTrue(isinstance(Product.name, property), "Name musí být property (použij @property)")
        self.assertTrue(isinstance(Product.price, property), "Price musí být property (použij @property)")
        self.assertTrue(isinstance(Product.quantity, property), "Quantity musí být property (použij @property)")

    def test_product_creation(self):
        p = Product("Test", 100.0, 5)
        self.assertEqual(p.name, "Test")
        self.assertEqual(p.price, 100.0)
        self.assertEqual(p.quantity, 5)

    def test_validation_name(self):
        with self.assertRaises(ValueError):
            Product("", 100, 1)
        
        p = Product("Valid", 100, 1)
        with self.assertRaises(ValueError):
            p.name = ""

    def test_validation_price(self):
        with self.assertRaises(ValueError):
            Product("Bad", -1.0, 1)
        
        p = Product("Valid", 100, 1)
        with self.assertRaises(ValueError):
            p.price = -0.5
            
        p.price = 0  # 0 is valid
        self.assertEqual(p.price, 0)

    def test_validation_quantity(self):
        with self.assertRaises(ValueError):
            Product("Bad", 100, -1)
            
        p = Product("Valid", 100, 1)
        with self.assertRaises(ValueError):
            p.quantity = -1
            
        p.quantity = 0 # 0 is valid
        self.assertEqual(p.quantity, 0)

class TestStorage(unittest.TestCase):
    def setUp(self):
        self.test_file = "test_inventory.json"
        self.storage = Storage(self.test_file)

    def tearDown(self):
        if os.path.exists(self.test_file):
            os.remove(self.test_file)

    def test_save_load(self):
        p = Product("TestItem", 50, 2)
        self.storage.save_products([p])
        
        loaded = self.storage.load_products()
        self.assertEqual(len(loaded), 1)
        self.assertEqual(loaded[0].name, "TestItem")
        self.assertEqual(loaded[0].price, 50)

    def test_load_corrupted_file(self):
        with open(self.test_file, "w") as f:
            f.write("{THIS IS NOT JSON}")
        
        products = self.storage.load_products()
        self.assertEqual(products, [], "Měl by vrátit prázdný list při chybě JSONu")

    def test_load_nonexistent_file(self):
        products = self.storage.load_products()
        self.assertEqual(products, [], "Měl by vrátit prázdný list, pokud soubor neexistuje")

class TestIntegration(unittest.TestCase):
    def setUp(self):
        self.test_file = "test_inventory_integration.json"
        # Ensure clean state
        if os.path.exists(self.test_file):
            os.remove(self.test_file)
        self.storage = Storage(self.test_file)

    def tearDown(self):
        if os.path.exists(self.test_file):
            os.remove(self.test_file)

    def test_manager_add_product(self):
        manager = InventoryManager(self.storage)
        # Capture stdout to avoid clutter
        capturedOutput = io.StringIO()
        sys.stdout = capturedOutput
        
        manager.add_product("Laptop", 20000, 5)
        
        sys.stdout = sys.__stdout__
        
        self.assertEqual(len(manager.products), 1)
        loaded = self.storage.load_products()
        self.assertEqual(len(loaded), 1)
        self.assertEqual(loaded[0].name, "Laptop")

if __name__ == "__main__":
    unittest.main()
