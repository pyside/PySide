project(QtScript)

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
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptprogram_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptstring_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptvalue_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/qscriptvalueiterator_wrapper.cpp

)

execute_generator(script QtScript_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript
                    ${QT_INCLUDE_DIR}
                    ${QT_QTSCRIPT_INCLUDE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${QtCore_BINARY_DIR}/PySide/QtCore
                    )
add_library(QtScript MODULE ${QtScript_SRC})
set_property(TARGET QtScript PROPERTY PREFIX "")
target_link_libraries(QtScript
                      pyside
                      ${PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTSCRIPT_LIBRARY}
                      )
add_dependencies(QtScript QtCore)

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtScript.so DESTINATION ${SITE_PACKAGE}/PySide)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtScript/pyside_qtscript_python.h
        DESTINATION include/PySide/QtScript/)

