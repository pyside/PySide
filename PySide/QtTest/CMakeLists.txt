project(QtTest)

set(QtTest_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtTest/qtest_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtTest/qttest_module_wrapper.cpp
)

set(QtTest_typesystem_path "${QtCore_SOURCE_DIR}${PATH_SEP}${QtGui_SOURCE_DIR}${PATH_SEP}${QtGui_BINARY_DIR}")
set(QtTest_include_dirs ${CMAKE_CURRENT_SOURCE_DIR}
                        ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtTest/
                        ${QT_INCLUDE_DIR}
                        ${QT_QTCORE_INCLUDE_DIR}
                        ${QT_QTGUI_INCLUDE_DIR}
                        ${QT_QTTEST_INCLUDE_DIR}
                        ${SHIBOKEN_INCLUDE_DIR}
                        ${libpyside_SOURCE_DIR}
                        ${SHIBOKEN_PYTHON_INCLUDE_DIR}
                        ${QtCore_BINARY_DIR}/PySide/QtCore/
                        ${QtGui_BINARY_DIR}/PySide/QtGui/)
set(QtTest_libraries    pyside
                        ${SHIBOKEN_PYTHON_LIBRARIES}
                        ${SHIBOKEN_LIBRARY}
                        ${QT_QTTEST_LIBRARY}
                        ${QT_QTGUI_LIBRARY}
                        ${QT_QTCORE_LIBRARY})
set(QtTest_deps  QtGui)
create_pyside_module(QtTest
                     QtTest_include_dirs
                     QtTest_libraries
                     QtTest_deps
                     QtTest_typesystem_path
                     QtTest_SRC
                     "")
