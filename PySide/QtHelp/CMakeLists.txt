project(QtHelp)

set(QtHelp_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpcontentitem_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpcontentmodel_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpcontentwidget_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpenginecore_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpengine_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpindexmodel_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpindexwidget_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpsearchengine_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpsearchquerywidget_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpsearchquery_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qhelpsearchresultwidget_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/qthelp_module_wrapper.cpp
)

execute_generator(help QtHelp_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtGui_SOURCE_DIR}:${QtHelp_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTGUI_INCLUDE_DIR}
                    ${QT_QTHELP_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${QtGui_BINARY_DIR}/PySide/QtGui/
                    ${QtCore_BINARY_DIR}/PySide/QtCore/
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp)
add_library(QtHelp MODULE ${QtHelp_SRC})

set_target_properties(QtHelp PROPERTIES PREFIX "")

target_link_libraries(QtHelp
                      pyside
                      ${PYSIDE_PYTHON_LIBRARIES}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      ${QT_QTHELP_LIBRARY})
add_dependencies(QtHelp QtGui)

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtHelp${CMAKE_DEBUG_POSTFIX}.so
        DESTINATION ${SITE_PACKAGE}/PySide)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtHelp/pyside_qthelp_python.h
        DESTINATION include/PySide/QtHelp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_help.xml
        DESTINATION share/PySide/typesystems)

