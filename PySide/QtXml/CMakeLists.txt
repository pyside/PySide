project(QtXml)

set(QtXml_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomattr_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomcdatasection_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomcharacterdata_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomcomment_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomdocument_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomdocumentfragment_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomdocumenttype_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomelement_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomentity_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomentityreference_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomimplementation_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomnamednodemap_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomnode_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomnodelist_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomnotation_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomprocessinginstruction_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qdomtext_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qtxml_module_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmlattributes_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmlcontenthandler_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmldeclhandler_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmldefaulthandler_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmldtdhandler_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmlentityresolver_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmlerrorhandler_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmlinputsource_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmllexicalhandler_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmllocator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmlnamespacesupport_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmlparseexception_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmlreader_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml/qxmlsimplereader_wrapper.cpp
)

execute_generator(xml QtXml_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtXml
                    ${CMAKE_SOURCE_DIR}
                    ${QT_INCLUDE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTXML_INCLUDE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${QtCore_BINARY_DIR}/PySide/QtCore
                    )
add_library(QtXml MODULE ${QtXml_SRC})
set_property(TARGET QtXml PROPERTY PREFIX "")
target_link_libraries(QtXml
                      pyside
                      ${PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
                      ${QT_QTXML_LIBRARY}
                      )
add_dependencies(QtXml QtCore)

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtXml.so DESTINATION ${SITE_PACKAGE}/PySide)

