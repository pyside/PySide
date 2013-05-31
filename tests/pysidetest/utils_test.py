# This file is part of PySide: Python for Qt
#
# Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
#
# Contact: PySide team <contact@pyside.org>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
# 02110-1301 USA

import unittest
import sys
import os


if sys.platform == 'win32':
    from PySide._utils import _get_win32_case_sensitive_name

    class Win32UtilsTest(unittest.TestCase):
        def testWin32CaseSensitiveName(self):
            from tempfile import mkdtemp
            caseSensitiveName = 'CaseSensitiveName'
            tmpdir = mkdtemp(caseSensitiveName)
            try:
                path = _get_win32_case_sensitive_name(tmpdir.lower())
                self.assertTrue(path.endswith(caseSensitiveName))
            finally:
                if os.path.exists(tmpdir):
                    os.rmdir(tmpdir)


if __name__ == '__main__':
    unittest.main()
