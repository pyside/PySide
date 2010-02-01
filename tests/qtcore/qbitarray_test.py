#!/usr/bin/python
'''Tests if QBitArray class is iterable and also '~' (__invert__) and bitwise operators'''

import unittest

from PySide.QtCore import QBitArray

def bool_list_from_qbitarray(qbitarray):
    '''This function is used instead of a list comprehension because
       the QBitArray is being tested also to check if it is providing
       the iterable protocol.
    '''
    qbitarray_values = []
    for i in range(qbitarray.size()):
        qbitarray_values.append(qbitarray.at(i))
    return qbitarray_values

class QBitArrayIsIterableTest(unittest.TestCase):
    '''Tests if QBitArray class is iterable and also '~' (__invert__) and bitwise operators'''

    def setUp(self):
        #Acquire resources
        self.qbitarray = QBitArray(3)
        self.qbitarray_values = [True, False, False]
        # WARNING: do not pythonify the following loop
        for i in range(len(self.qbitarray_values)):
            self.qbitarray.setBit(i, self.qbitarray_values[i])

        self.inverted_qbitarray_values = [not bit for bit in self.qbitarray_values]

        self.other_qbitarray = QBitArray(3)
        self.other_qbitarray_values = [True, True, False]
        # WARNING: do not pythonify the following loop
        for i in range(len(self.other_qbitarray_values)):
            self.other_qbitarray.setBit(i, self.other_qbitarray_values[i])

    def tearDown(self):
        #Release resources
        del self.qbitarray
        del self.other_qbitarray
        del self.qbitarray_values
        del self.other_qbitarray_values
        del self.inverted_qbitarray_values

    def testQBitArrayIsIterable(self):
        #Tests if QBitArray class is iterable
        qbitarray_is_iterable = True
        try:
            bitarray = [bit for bit in self.qbitarray]
        except:
            qbitarray_is_iterable = False
        self.assertTrue(qbitarray_is_iterable)

    def testQBitArrayInvertOperator(self):
        #Tests QBitArray '~' (__invert__) operator
        inverted_qbitarray = ~self.qbitarray
        # WARNING: do not pythonify the following loop, the
        # iterability of QBitArray class is tested in another place
        inverted_qbitarray_values = bool_list_from_qbitarray(inverted_qbitarray)
        self.assertEqual(self.inverted_qbitarray_values, inverted_qbitarray_values)

    def testQBitArrayOrBitwiseOperator(self):
        #Tests QBitArray '|' (or) operator
        has_or_bitwise_operator = True
        ored_qbitarray, ored_bool_list = None, None
        try:
            ored_qbitarray = self.qbitarray | self.other_qbitarray
            ored_bool_list = [b1 | b2 for b1, b2 in zip(self.qbitarray_values, self.other_qbitarray_values)]
        except:
            has_or_bitwise_operator = False
        self.assertTrue(has_or_bitwise_operator)
        self.assertEqual(bool_list_from_qbitarray(ored_qbitarray), ored_bool_list)

    def testQBitArrayAndBitwiseOperator(self):
        #Tests QBitArray '&' (and) operator
        has_and_bitwise_operator = True
        anded_qbitarray, anded_bool_list = None, None
        try:
            anded_qbitarray = self.qbitarray | self.other_qbitarray
            anded_bool_list = [b1 | b2 for b1, b2 in zip(self.qbitarray_values, self.other_qbitarray_values)]
        except:
            has_and_bitwise_operator = False
        self.assertTrue(has_and_bitwise_operator)
        self.assertEqual(bool_list_from_qbitarray(anded_qbitarray), anded_bool_list)

    def testQBitArrayXorBitwiseOperator(self):
        #Tests QBitArray '^' (xor) operator
        has_xor_bitwise_operator = True
        xored_qbitarray, xored_bool_list = None, None
        try:
            xored_qbitarray = self.qbitarray | self.other_qbitarray
            xored_bool_list = [b1 | b2 for b1, b2 in zip(self.qbitarray_values, self.other_qbitarray_values)]
        except:
            has_xor_bitwise_operator = False
        self.assertTrue(has_xor_bitwise_operator)
        self.assertEqual(bool_list_from_qbitarray(xored_qbitarray), xored_bool_list)


class QBitArrayGetItemTest(unittest.TestCase):
    '''Test case for []/__getitem__ operator'''

    def create_bitarray(self, values):
        '''helper function to create a bit array'''
        obj = QBitArray(len(values))
        for i, value in enumerate(values):
            obj.setBit(i, value)
        return obj

    def testSequenceProtocol(self):
        '''QBitArray sequence protocol'''
        data = [True, False, True]
        obj = self.create_bitarray(data)
        for reference, value in zip(data, obj):
            self.assertEqual(reference, value)


if __name__ == '__main__':
    unittest.main()

