project(QtSvg)

if(Q_WS_X11)
    set(MODULE_NAME svg_x11)
    set(SPECIFIC_OS_FILES
       )
elseif(Q_WS_MAC)
    set(MODULE_NAME svg_mac)
    set(SPECIFIC_OS_FILES
       )
else()
    message(FATAL_ERROR "OS not supported")
endif(Q_WS_X11)

if (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 6)
    set (QtSvg_46_SRC )
else ()
    set(QtSvg_46_SRC
    )
endif (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 6)

set(QtSvg_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSvg/qgraphicssvgitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSvg/qsvggenerator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSvg/qsvgrenderer_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSvg/qsvgwidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSvg/qtsvg_module_wrapper.cpp

${SPECIFIC_OS_FILES}
${QtSvg_46_SRC}
)

set(QtSvg_typesystem_path "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}")
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
                        ${PYSIDE_PYTHON_LIBRARIES}
                        ${SHIBOKEN_LIBRARY}
                        ${QT_QTSVG_LIBRARY}
                        ${QT_QTGUI_LIBRARY})
set(QtSvg_deps QtGui)
create_pyside_module(QtSvg
                     ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_svg.xml
                     QtSvg_include_dirs
                     QtSvg_libraries
                     QtSvg_deps
                     QtSvg_typesystem_path
                     QtSvg_SRC)
