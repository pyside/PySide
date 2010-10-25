project(QtSvg)

set(QtSvg_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSvg/qgraphicssvgitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSvg/qsvggenerator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSvg/qsvgrenderer_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSvg/qsvgwidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSvg/qtsvg_module_wrapper.cpp
)

set(QtSvg_typesystem_path "${QtCore_SOURCE_DIR}${PATH_SEP}${QtGui_SOURCE_DIR}${PATH_SEP}${QtGui_BINARY_DIR}")
set(QtSvg_include_dirs  ${CMAKE_CURRENT_SOURCE_DIR}
                        ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSvg/
                        ${QT_INCLUDE_DIR}
                        ${QT_QTCORE_INCLUDE_DIR}
                        ${QT_QTGUI_INCLUDE_DIR}
                        ${QT_QTSVG_INCLUDE_DIR}
                        ${SHIBOKEN_INCLUDE_DIR}
                        ${libpyside_SOURCE_DIR}
                        ${PYTHON_INCLUDE_PATH}
                        ${QtCore_BINARY_DIR}/PySide/QtCore/
                        ${QtGui_BINARY_DIR}/PySide/QtGui/)
set(QtSvg_libraries     pyside
                        ${SHIBOKEN_PYTHON_LIBRARIES}
                        ${SHIBOKEN_LIBRARY}
                        ${QT_QTSVG_LIBRARY}
                        ${QT_QTGUI_LIBRARY})
set(QtSvg_deps QtGui)
create_pyside_module(QtSvg
                     QtSvg_include_dirs
                     QtSvg_libraries
                     QtSvg_deps
                     QtSvg_typesystem_path
                     QtSvg_SRC
                     "")
