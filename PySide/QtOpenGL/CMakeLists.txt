project(QtOpenGL)

if (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 6)
  set(QtOpenGL_46_SRC )
else()
  set(QtOpenGL_46_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/qglframebufferobjectformat_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/qglshaderprogram_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/qglshader_wrapper.cpp
  )
endif()

if (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 7)
  set(QtOpenGL_47_SRC )
else()
  set(QtOpenGL_47_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/qglbuffer_wrapper.cpp
  )
endif()


set(QtOpenGL_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/qgl_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/qglcolormap_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/qglcontext_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/qglformat_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/qglframebufferobject_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/qglpixelbuffer_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/qglwidget_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/qtopengl_module_wrapper.cpp
    ${QtOpenGL_46_SRC}
    ${QtOpenGL_47_SRC}
)

set(QtOpenGL_typesystem_path "${QtCore_SOURCE_DIR}${PATH_SEP}${QtGui_SOURCE_DIR}${PATH_SEP}${QtOpenGL_SOURCE_DIR}${PATH_SEP}${QtGui_BINARY_DIR}")
set(QtOpenGL_include_dirs   ${CMAKE_CURRENT_SOURCE_DIR}
                            ${QT_QTCORE_INCLUDE_DIR}
                            ${QT_QTGUI_INCLUDE_DIR}
                            ${QT_QTOPENGL_INCLUDE_DIR}
                            ${PYTHON_INCLUDE_PATH}
                            ${SHIBOKEN_INCLUDE_DIR}
                            ${libpyside_SOURCE_DIR}
                            ${QtGui_BINARY_DIR}/PySide/QtGui/
                            ${QtCore_BINARY_DIR}/PySide/QtCore/
                            ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL)
set(QtOpenGL_libraries      pyside
                            ${SHIBOKEN_PYTHON_LIBRARIES}
                            ${QT_QTCORE_LIBRARY}
                            ${QT_QTGUI_LIBRARY}
                            ${QT_QTOPENGL_LIBRARY})
set(QtOpenGL_deps QtGui)
create_pyside_module(QtOpenGL
                    QtOpenGL_include_dirs
                    QtOpenGL_libraries
                    QtOpenGL_deps
                    QtOpenGL_typesystem_path
                    QtOpenGL_SRC
                    "")
