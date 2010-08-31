project(QtDeclarative)

set(QtDeclarative_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativecomponent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativecontext_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativeengine_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativeerror_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativeexpression_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativeextensioninterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativeextensionplugin_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativeimageprovider_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativeitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativelistreference_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativenetworkaccessmanagerfactory_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativeparserstatus_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativepropertymap_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativepropertyvaluesource_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativeproperty_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativescriptstring_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qdeclarativeview_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative/qtdeclarative_module_wrapper.cpp
)

set(QtDeclarative_typesystem_path "${QtCore_SOURCE_DIR}${PATH_SEP}${QtGui_SOURCE_DIR}${PATH_SEP}${QtNetwork_SOURCE_DIR}${PATH_SEP}${QtDeclarative_SOURCE_DIR}${PATH_SEP}${QtGui_BINARY_DIR}")

set(QtDeclarative_include_dirs  ${CMAKE_CURRENT_SOURCE_DIR}
                            ${QT_QTCORE_INCLUDE_DIR}
                            ${QT_QTGUI_INCLUDE_DIR}
                            ${QT_QTNETWORK_INCLUDE_DIR}
                            ${QT_QTDECLARATIVE_INCLUDE_DIR}
                            ${PYTHON_INCLUDE_PATH}
                            ${SHIBOKEN_INCLUDE_DIR}
                            ${libpyside_SOURCE_DIR}
                            ${QtGui_BINARY_DIR}/PySide/QtGui/
                            ${QtCore_BINARY_DIR}/PySide/QtCore/
                            ${QtNetwork_BINARY_DIR}/PySide/QtNetwork/
                            ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtDeclarative)

set(QtDeclarative_libraries   pyside
                              ${PYSIDE_PYTHON_LIBRARIES}
                              ${QT_QTCORE_LIBRARY}
                              ${QT_QTGUI_LIBRARY}
                              ${QT_QTNETWORK_LIBRARY}
                              ${QT_QTSCRIPT_LIBRARY}
                              ${QT_QTSVG_LIBRARY}
                              ${QT_QTSQL_LIBRARY}
                              ${QT_QTXMLPATTERNS_LIBRARY}
                              ${QT_QTOPENGL_LIBRARY}
                              ${QT_QTDECLARATIVE_LIBRARY})

set(QtDeclarative_deps QtGui QtNetwork)

create_pyside_module(QtDeclarative
                     QtDeclarative_include_dirs
                     QtDeclarative_libraries
                     QtDeclarative_deps
                     QtDeclarative_typesystem_path
                     QtDeclarative_SRC
                     "")

