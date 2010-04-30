project(QtScriptTools)

set(QtScriptTools_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScriptTools/qtscripttools_module_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScriptTools/qscriptenginedebugger_wrapper.cpp
)

execute_generator(scripttools QtScriptTools_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtScript_SOURCE_DIR}:${QtScriptTools_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_GUI_INCLUDE_DIR}
                    ${QT_QTSCRIPT_INCLUDE_DIR}
                    ${QT_QTSCRIPTTOOLS_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${QtCore_BINARY_DIR}/PySide/QtCore/
                    ${QtGui_BINARY_DIR}/PySide/QtGui/
                    ${QtScript_BINARY_DIR}/PySide/QtScript/
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScriptTools)

add_library(QtScriptTools MODULE ${QtScriptTools_SRC})
set_target_properties(QtScriptTools PROPERTIES PREFIX "")
target_link_libraries(QtScriptTools
                      pyside
                      ${PYTHON_LIBRARIES}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_GUI_LIBRARY}
                      ${QT_QTSCRIPT_LIBRARY}
                      ${QT_QTSCRIPTTOOLS_LIBRARY})

add_dependencies(QtScriptTools QtCore QtScript QtGui)

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtScriptTools.so
        DESTINATION ${SITE_PACKAGE}/PySide)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScriptTools/pyside_qtscripttools_python.h
        DESTINATION include/PySide/QtScriptTools/)

