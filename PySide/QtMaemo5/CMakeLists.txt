project(QtMaemo5)

set(QtMaemo5_SRC
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtMaemo5/qmaemo5abstractpickselector_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtMaemo5/qmaemo5datepickselector_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtMaemo5/qmaemo5editbar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtMaemo5/qmaemo5informationbox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtMaemo5/qmaemo5listpickselector_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtMaemo5/qmaemo5timepickselector_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtMaemo5/qmaemo5valuebutton_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtMaemo5/qtmaemo5_module_wrapper.cpp
)

set(QtMaemo5_typesystem_path "${QtCore_SOURCE_DIR}${PATH_SEP}${QtGui_SOURCE_DIR}${PATH_SEP}${QtMaemo5_SOURCE_DIR}")

# QT_QTMAEMO5_* variables are not defined by CMake
if(NOT QT_QTMAEMO5_INCLUDE_DIR)
  FIND_PATH(QT_QTMAEMO5_INCLUDE_DIR QtMaemo5
            PATHS ${QT_HEADERS_DIR}/QtMaemo5 NO_DEFAULT_PATH)
endif()
if(NOT QT_QTMAEMO5_LIBRARY)
  FIND_LIBRARY(QT_QTMAEMO5_LIBRARY QtMaemo5
               PATHS ${QT_LIBRARY_DIR} NO_DEFAULT_PATH)
endif()

set(QtMaemo5_include_dirs ${CMAKE_CURRENT_SOURCE_DIR}
                        ${QT_QTCORE_INCLUDE_DIR}
                        ${QT_QTGUI_INCLUDE_DIR}
                        ${QT_QTMAEMO5_INCLUDE_DIR}
                        ${SHIBOKEN_PYTHON_INCLUDE_DIR}
                        ${SHIBOKEN_INCLUDE_DIR}
                        ${libpyside_SOURCE_DIR}
                        ${QtCore_BINARY_DIR}/${BINDING_NAME}/QtCore/
                        ${QtGui_BINARY_DIR}/${BINDING_NAME}/QtGui/
                        ${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtMaemo5)
set(QtMaemo5_libraries  pyside
                      ${SHIBOKEN_PYTHON_LIBRARIES}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      ${QT_QTMAEMO5_LIBRARY})
set(QtMaemo5_deps QtGui)

create_pyside_module(QtMaemo5
                     QtMaemo5_include_dirs
                     QtMaemo5_libraries
                     QtMaemo5_deps
                     QtMaemo5_typesystem_path
                     QtMaemo5_SRC
                     "")

