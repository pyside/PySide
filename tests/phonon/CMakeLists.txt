if (NOT WIN32 OR NOT ${QTVERSION} VERSION_EQUAL 4.7.1)
    # Any usage of Phonon::createPath will fail on Win32 and Qt 4.7.1.
    # Check: http://bugreports.qt.nokia.com/browse/QTBUG-13062
    PYSIDE_TEST(basic_playing_test.py)
endif()
PYSIDE_TEST(bug_328.py)
PYSIDE_TEST(capabilities_test.py)
PYSIDE_TEST(qobjectdescription_test.py)
