project(QtXmlPatterns)

if (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 6)
    set(QtXmlPatterns_46_SRC )
else()
    set(QtXmlPatterns_46_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qxmlschemavalidator_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qxmlschema_wrapper.cpp
    )
endif()

set(QtXmlPatterns_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qabstractmessagehandler_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qabstracturiresolver_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qabstractxmlnodemodel_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qabstractxmlreceiver_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qsourcelocation_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qtxmlpatterns_module_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qxmlformatter_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qxmlitem_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qxmlnamepool_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qxmlname_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qxmlnodemodelindex_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qxmlquery_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qxmlresultitems_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/qxmlserializer_wrapper.cpp
    ${QtXmlPatterns_46_SRC}
)

execute_generator(xmlpatterns QtXmlPatterns_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTXMLPATTERNS_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${QtCore_BINARY_DIR}/PySide/QtCore/
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns)
add_library(QtXmlPatterns MODULE ${QtXmlPatterns_SRC})
set_target_properties(QtXmlPatterns PROPERTIES PREFIX "")
target_link_libraries(QtXmlPatterns
                      pyside
                      ${PYSIDE_PYTHON_LIBRARIES}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTXMLPATTERNS_LIBRARY})
add_dependencies(QtXmlPatterns QtCore)
# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtXmlPatterns${CMAKE_DEBUG_POSTFIX}.so
        DESTINATION ${SITE_PACKAGE}/PySide)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXmlPatterns/pyside_qtxmlpatterns_python.h
        DESTINATION include/PySide/QtXmlPatterns/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_xmlpatterns.xml
        DESTINATION share/PySide/typesystems)

