from testbinding import *
import unittest

class TestBug1016 (unittest.TestCase):

    def testIt(self):
        obj = getHiddenObject()
        self.assertEqual(obj.callMe(), None)
        self.assertTrue(obj.wasCalled())

if __name__ == "__main__":
    unittest.main()
