if(${QTVERSION} VERSION_GREATER 4.6.9)
    PYSIDE_TEST(qglbuffer_test.py)
endif()
PYSIDE_TEST(qglwidget_test.py)
