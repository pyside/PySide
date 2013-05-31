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

import sys
import os


if sys.platform == 'win32':
    # On Windows get the PySide package path in case sensitive format.
    # Even if the file system on Windows is case insensitive,
    # some parts in Qt environment such as qml imports path,
    # requires to be in case sensitive format.
    import ctypes
    from ctypes import POINTER, WinError, sizeof, byref, create_unicode_buffer
    from ctypes.wintypes import MAX_PATH, LPCWSTR, LPWSTR, DWORD

    GetShortPathNameW = ctypes.windll.kernel32.GetShortPathNameW
    GetShortPathNameW.argtypes = [LPCWSTR, LPWSTR, DWORD]
    GetShortPathNameW.restype = DWORD

    GetLongPathNameW = ctypes.windll.kernel32.GetLongPathNameW
    GetLongPathNameW.argtypes = [LPCWSTR, LPWSTR, DWORD]
    GetLongPathNameW.restype = DWORD

    PY_2 = sys.version_info[0] < 3

    if PY_2:
        def u(x):
            return unicode(x)
    else:
        def u(x):
            return x

    def _get_win32_short_name(s):
        """ Returns short name """
        buf_size = MAX_PATH
        for i in range(2):
            buf = create_unicode_buffer(u('\0') * (buf_size + 1))
            r = GetShortPathNameW(u(s), buf, buf_size)
            if r == 0:
                raise WinError()
            if r < buf_size:
                if PY_2:
                    return buf.value.encode(sys.getfilesystemencoding())
                return buf.value
            buf_size = r
        raise WinError()

    def _get_win32_long_name(s):
        """ Returns long name """
        buf_size = MAX_PATH
        for i in range(2):
            buf = create_unicode_buffer(u('\0') * (buf_size + 1))
            r = GetLongPathNameW(u(s), buf, buf_size)
            if r == 0:
                raise WinError()
            if r < buf_size:
                if PY_2:
                    return buf.value.encode(sys.getfilesystemencoding())
                return buf.value
            buf_size = r
        raise WinError()

    def _get_win32_case_sensitive_name(s):
        """ Returns long name in case sensitive format """
        path = _get_win32_long_name(_get_win32_short_name(s))
        return path

    def get_pyside_dir():
        return _get_win32_case_sensitive_name(os.path.abspath(os.path.dirname(__file__)))

else:
    def get_pyside_dir():
        return os.path.abspath(os.path.dirname(__file__))
