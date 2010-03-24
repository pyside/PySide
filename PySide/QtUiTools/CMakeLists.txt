project(QtUiTools)

set(QtUiTools_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtUiTools/qtuitools_module_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtUiTools/quiloader_wrapper.cpp
)

execute_generator(uitools QtUiTools_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtGui_SOURCE_DIR}:${QtXml_SOURCE_DIR}:${QtUiTools_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTGUI_INCLUDE_DIR}
                    ${QT_QTXML_INCLUDE_DIR}
                    ${QT_QTUITOOLS_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${QtCore_BINARY_DIR}/PySide/QtCore/
                    ${QtXml_BINARY_DIR}/PySide/QtXml/
                    ${QtGui_BINARY_DIR}/PySide/QtGui/
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtUiTools)

add_library(QtUiTools MODULE ${QtUiTools_SRC})
set_target_properties(QtUiTools PROPERTIES PREFIX "")
target_link_libraries(QtUiTools
                      pyside
                      ${PYTHON_LIBRARIES}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      ${QT_QTXML_LIBRARY}
                      ${QT_QTUITOOLS_LIBRARY})

add_dependencies(QtUiTools QtGui QtXml)

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtUiTools.so
        DESTINATION ${SITE_PACKAGE}/PySide)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtUiTools/pyside_qtuitools_python.h
        DESTINATION include/PySide/QtUiTools/)

