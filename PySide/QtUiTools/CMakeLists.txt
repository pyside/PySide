project(QtUiTools)

set(QtUiTools_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtUiTools/qtuitools_module_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtUiTools/quiloader_wrapper.cpp
)

set(QtUiTools_typesystem_path "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtGui_SOURCE_DIR}:${QtXml_SOURCE_DIR}:${QtUiTools_SOURCE_DIR}")
set(QtUiTools_include_dirs  ${CMAKE_CURRENT_SOURCE_DIR}
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
set(QtUiTools_libraries     pyside
                            ${PYSIDE_PYTHON_LIBRARIES}
                            ${QT_QTCORE_LIBRARY}
                            ${QT_QTGUI_LIBRARY}
                            ${QT_QTUITOOLS_LIBRARY})
set(QtUiTools_deps QtGui QtXml)
create_pyside_module(QtUiTools
                     ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_uitools.xml
                     QtUiTools_include_dirs
                     QtUiTools_libraries
                     QtUiTools_deps
                     QtUiTools_typesystem_path
                     QtUiTools_SRC)
