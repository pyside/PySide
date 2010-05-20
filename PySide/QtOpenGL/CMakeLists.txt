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
)

execute_generator(opengl QtOpenGL_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtGui_SOURCE_DIR}:${QtOpenGL_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTGUI_INCLUDE_DIR}
                    ${QT_QTOPENGL_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${QtGui_BINARY_DIR}/PySide/QtGui/
                    ${QtCore_BINARY_DIR}/PySide/QtCore/
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL)
add_library(QtOpenGL MODULE ${QtOpenGL_SRC})
set_target_properties(QtOpenGL PROPERTIES PREFIX "")
target_link_libraries(QtOpenGL
                      pyside
                      ${PYTHON_LIBRARIES}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      ${QT_QTOPENGL_LIBRARY})
add_dependencies(QtOpenGL QtGui)

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtOpenGL${CMAKE_DEBUG_POSTFIX}.so
        DESTINATION ${SITE_PACKAGE}/PySide)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtOpenGL/pyside_qtopengl_python.h
        DESTINATION include/PySide/QtOpenGL/)

