import unittest
from hello_world import hello_world


class TestFunkci(unittest.TestCase):

    def test_hello_world(self):
        self.assertEqual(hello_world(), "Hello world!")


if __name__ == '__main__':
    unittest.main()
