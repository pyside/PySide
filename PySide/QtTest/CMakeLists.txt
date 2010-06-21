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

execute_generator(test QtTest_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtTest/
                    ${QT_INCLUDE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTGUI_INCLUDE_DIR}
                    ${QT_QTTEST_INCLUDE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${QtCore_BINARY_DIR}/PySide/QtCore/
                    ${QtGui_BINARY_DIR}/PySide/QtGui/
                    )

add_library(QtTest MODULE ${QtTest_SRC})
set_property(TARGET QtTest PROPERTY PREFIX "")
target_link_libraries(QtTest
                      ${PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
                      ${QT_QTTEST_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      ${QT_QTCORE_LIBRARY}
                      )
add_dependencies(QtTest QtGui)

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtTest${CMAKE_DEBUG_POSTFIX}.so
        DESTINATION ${SITE_PACKAGE}/PySide)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtTest/pyside_qttest_python.h
        DESTINATION include/PySide/QtTest/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_test.xml
        DESTINATION share/PySide/typesystems)

