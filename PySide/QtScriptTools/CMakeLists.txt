project(QtScriptTools)

set(QtScriptTools_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScriptTools/qtscripttools_module_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScriptTools/qscriptenginedebugger_wrapper.cpp
)

set(QtScriptTools_typesystem_path "${QtCore_SOURCE_DIR}${PATH_SEP}${QtGui_SOURCE_DIR}${PATH_SEP}${QtScript_SOURCE_DIR}${PATH_SEP}${QtScriptTools_SOURCE_DIR}${PATH_SEP}${QtGui_BINARY_DIR}")

set(QtScriptTools_include_dirs ${CMAKE_CURRENT_SOURCE_DIR}
                                ${QT_QTCORE_INCLUDE_DIR}
                                ${QT_GUI_INCLUDE_DIR}
                                ${QT_QTSCRIPT_INCLUDE_DIR}
                                ${QT_QTSCRIPTTOOLS_INCLUDE_DIR}
                                ${SHIBOKEN_PYTHON_INCLUDE_DIR}
                                ${SHIBOKEN_INCLUDE_DIR}
                                ${libpyside_SOURCE_DIR}
                                ${QtCore_BINARY_DIR}/PySide/QtCore/
                                ${QtGui_BINARY_DIR}/PySide/QtGui/
                                ${QtScript_BINARY_DIR}/PySide/QtScript/
                                ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScriptTools)

set(QtScriptTools_libraries     pyside
                                ${SHIBOKEN_PYTHON_LIBRARIES}
                                ${QT_QTCORE_LIBRARY}
                                ${QT_GUI_LIBRARY}
                                ${QT_QTSCRIPT_LIBRARY}
                                ${QT_QTSCRIPTTOOLS_LIBRARY})
set(QtScriptTools_deps QtCore QtScript QtGui)

create_pyside_module(QtScriptTools
                     QtScriptTools_include_dirs
                     QtScriptTools_libraries
                     QtScriptTools_deps
                     QtScriptTools_typesystem_path
                     QtScriptTools_SRC
                     "")
