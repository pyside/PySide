project(QtCore)

set(QtCore_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtCore/qregexp_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtCore/qchar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtCore/qstring_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtCore/qstring_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtCore/qpoint_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtCore/qpointf_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtCore/qrect_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtCore/qrectf_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtCore/qsize_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtCore/qsizef_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtCore/qtcore_module_wrapper.cpp
)

execute_generator(core QtCore_SRC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtCore/
                    ${QT_INCLUDE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    )
add_library(QtCore MODULE ${QtCore_SRC})
set_property(TARGET QtCore PROPERTY PREFIX "")
target_link_libraries(QtCore
                      ${PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
                      ${QT_QTCORE_LIBRARY}
                      )

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtCore.so
        DESTINATION ${SITE_PACKAGE}/${BINDING_NAME})
