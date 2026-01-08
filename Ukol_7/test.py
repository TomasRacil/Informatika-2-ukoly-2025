        # Původní vektory se nesmí změnit
        self.assertEqual(v1.x, 1)

    def test_sub(self):
        v1 = Vector2D(5, 5)
        v2 = Vector2D(2, 3)
        v3 = v1 - v2
        self.assertEqual(v3.x, 3)
        self.assertEqual(v3.y, 2)

    def test_mul_scalar(self):
        v1 = Vector2D(2, 3)
        v3 = v1 * 3
        self.assertIsInstance(v3, Vector2D)
        self.assertEqual(v3.x, 6)
        self.assertEqual(v3.y, 9)

    def test_mul_dot_product(self):
        v1 = Vector2D(2, 3)
        v2 = Vector2D(4, 5)
        # 2*4 + 3*5 = 8 + 15 = 23
        result = v1 * v2
        self.assertTrue(isinstance(result, (int, float)))
        self.assertEqual(result, 23)

    def test_eq(self):
        v1 = Vector2D(1, 1)
        v2 = Vector2D(1, 1)
        v3 = Vector2D(1, 2)
        self.assertTrue(v1 == v2)
        self.assertFalse(v1 == v3)

    def test_abs(self):
        # 3-4-5 trojúhelník
        v = Vector2D(3, 4)
        self.assertEqual(abs(v), 5.0)
        
        v2 = Vector2D(1, 1)
        self.assertAlmostEqual(abs(v2), 1.41421356, places=5)

if __name__ == '__main__':
    unittest.main()