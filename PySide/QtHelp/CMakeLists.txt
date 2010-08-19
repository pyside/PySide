project(QtHelp)

set(QtHelp_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpcontentitem_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpcontentmodel_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpcontentwidget_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpenginecore_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpengine_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpindexmodel_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpindexwidget_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpsearchengine_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpsearchquerywidget_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpsearchquery_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpsearchresultwidget_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qthelp_module_wrapper.cpp
)

set(QtHelp_typesystem_path "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtGui_SOURCE_DIR}:${QtHelp_SOURCE_DIR}")
set(QtHelp_include_dirs ${CMAKE_CURRENT_SOURCE_DIR}
                        ${QT_QTCORE_INCLUDE_DIR}
                        ${QT_QTGUI_INCLUDE_DIR}
                        ${QT_QTHELP_INCLUDE_DIR}
                        ${PYTHON_INCLUDE_PATH}
                        ${SHIBOKEN_INCLUDE_DIR}
                        ${libpyside_SOURCE_DIR}
                        ${QtGui_BINARY_DIR}/PySide/QtGui/
                        ${QtCore_BINARY_DIR}/PySide/QtCore/
                        ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp)
set(QtHelp_libraries  pyside
                      ${PYSIDE_PYTHON_LIBRARIES}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      ${QT_QTHELP_LIBRARY})
set(QtHelp_deps QtGui)

create_pyside_module(QtHelp
                     ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_help.xml
                     QtHelp_include_dirs
                     QtHelp_libraries
                     QtHelp_deps
                     QtHelp_typesystem_path
                     QtHelp_SRC)
