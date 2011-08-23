project(QtScript)

if (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 7)
    set (QtScript_47_SRC )
else()
    set(QtScript_47_SRC
        ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptprogram_wrapper.cpp
    )
endif()

set(QtScript_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptable_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptclass_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptclasspropertyiterator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptcontext_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptcontextinfo_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptengineagent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qtscript_module_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptengine_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptextensioninterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptextensionplugin_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptstring_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptvalue_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptvalueiterator_wrapper.cpp
${QtScript_47_SRC}
)

set(QtScript_typesystem_path "${QtCore_SOURCE_DIR}")
set(QtScript_include_dirs   ${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript
                            ${QT_INCLUDE_DIR}
                            ${QT_QTSCRIPT_INCLUDE_DIR}
                            ${SHIBOKEN_INCLUDE_DIR}
                            ${libpyside_SOURCE_DIR}
                            ${SHIBOKEN_PYTHON_INCLUDE_DIR}
                            ${QtCore_BINARY_DIR}/PySide/QtCore )
set(QtScript_libraries      pyside
                            ${SHIBOKEN_PYTHON_LIBRARIES}
                            ${SHIBOKEN_LIBRARY}
                            ${QT_QTCORE_LIBRARY}
                            ${QT_QTSCRIPT_LIBRARY})
set(QtScript_deps QtCore)
create_pyside_module(QtScript
                     QtScript_include_dirs
                     QtScript_libraries
                     QtScript_deps
                     QtScript_typesystem_path
                     QtScript_SRC
                     "")
