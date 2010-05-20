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

execute_generator(maemo5 QtMaemo5_SRC
                  "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtGui_SOURCE_DIR}:${QtMaemo5_SOURCE_DIR}")

# QT_QTMAEMO5_* variables are not defined by CMake
if(NOT QT_QTMAEMO5_INCLUDE_DIR)
  FIND_PATH(QT_QTMAEMO5_INCLUDE_DIR QtMaemo5
            PATHS ${QT_HEADERS_DIR}/QtMaemo5 NO_DEFAULT_PATH)
endif(NOT QT_QTMAEMO5_INCLUDE_DIR)
if(NOT QT_QTMAEMO5_LIBRARY)
  FIND_LIBRARY(QT_QTMAEMO5_LIBRARY QtMaemo5
               PATHS ${QT_LIBRARY_DIR} NO_DEFAULT_PATH)
endif(NOT QT_QTMAEMO5_LIBRARY)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTGUI_INCLUDE_DIR}
                    ${QT_QTMAEMO5_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${QtCore_BINARY_DIR}/${BINDING_NAME}/QtCore/
                    ${QtGui_BINARY_DIR}/${BINDING_NAME}/QtGui/
                    ${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtMaemo5)
add_library(QtMaemo5 MODULE ${QtMaemo5_SRC})

set_target_properties(QtMaemo5 PROPERTIES
                      PREFIX "")

target_link_libraries(QtMaemo5
                      pyside
                      ${PYTHON_LIBRARIES}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      ${QT_QTMAEMO5_LIBRARY})

#add_dependencies(QtMaemo5)

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtMaemo5${CMAKE_DEBUG_POSTFIX}.so
        DESTINATION ${SITE_PACKAGE}/${BINDING_NAME})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMaemo5/pyside_qtmaemo5_python.h
        DESTINATION include/${BINDING_NAME}/QtMaemo5/)

