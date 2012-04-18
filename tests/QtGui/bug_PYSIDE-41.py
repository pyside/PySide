# TODO:
# move this to QtCore -- QStringListModel is part of QtGui and there is no
# simple model class appropriate for this test in QtCore.

import unittest

from PySide.QtCore import *
from PySide.QtGui import *


class TestBugPYSIDE41(unittest.TestCase):

    def testIt(self):

        # list of single-character strings
        strings = list('abcdefghijklmnopqrstuvwxyz')

        model = QStringListModel(strings)

        # Test hashing of both QModelIndex and QPersistentModelIndex
        indexFunctions = []
        indexFunctions.append(model.index)
        indexFunctions.append(lambda i: QPersistentModelIndex(model.index(i)))

        for indexFunction in indexFunctions:

            # If two objects compare equal, their hashes MUST also be equal. (The
            # reverse is not a requirement.)
            for i, _ in enumerate(strings):
                index1 = indexFunction(i)
                index2 = indexFunction(i)
                self.assertEqual(index1, index2)
                self.assertEqual(hash(index1), hash(index2))

            # Adding the full set of indexes to itself is a no-op.
            allIndexes1 = set(indexFunction(i) for i, _ in enumerate(strings))
            allIndexes2 = set(indexFunction(i) for i, _ in enumerate(strings))
            allIndexesCombined = allIndexes1 & allIndexes2
            self.assertEqual(allIndexes1, allIndexesCombined)
            self.assertEqual(allIndexes2, allIndexesCombined)


if __name__ == '__main__':
    unittest.main()
