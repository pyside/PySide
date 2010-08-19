project(QtTest)

if(Q_WS_X11)
    set(MODULE_NAME test_x11)
    set(SPECIFIC_OS_FILES
       )
elseif(Q_WS_MAC)
    set(MODULE_NAME test_mac)
    set(SPECIFIC_OS_FILES
       )
else()
    message(FATAL_ERROR "OS not supported")
endif(Q_WS_X11)

set(QtTest_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtTest/qtest_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtTest/qttest_module_wrapper.cpp
${SPECIFIC_OS_FILES}
)

set(QtTest_typesystem_path "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}")
set(QtTest_include_dirs ${CMAKE_CURRENT_SOURCE_DIR}
                        ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtTest/
                        ${QT_INCLUDE_DIR}
                        ${QT_QTCORE_INCLUDE_DIR}
                        ${QT_QTGUI_INCLUDE_DIR}
                        ${QT_QTTEST_INCLUDE_DIR}
                        ${SHIBOKEN_INCLUDE_DIR}
                        ${libpyside_SOURCE_DIR}
                        ${PYTHON_INCLUDE_PATH}
                        ${QtCore_BINARY_DIR}/PySide/QtCore/
                        ${QtGui_BINARY_DIR}/PySide/QtGui/)
set(QtTest_libraries    pyside
                        ${PYSIDE_PYTHON_LIBRARIES}
                        ${SHIBOKEN_LIBRARY}
                        ${QT_QTTEST_LIBRARY}
                        ${QT_QTGUI_LIBRARY}
                        ${QT_QTCORE_LIBRARY})
set(QtTest_deps  QtGui)
create_pyside_module(QtTest
                     ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_test.xml
                     QtTest_include_dirs
                     QtTest_libraries
                     QtTest_deps
                     QtTest_typesystem_path
                     QtTest_SRC)
