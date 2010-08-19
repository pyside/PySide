project(QtWebKit)

if(Q_WS_X11)
    set(MODULE_NAME webkit_x11)
    set(SPECIFIC_OS_FILES
       )
elseif(Q_WS_MAC)
    set(MODULE_NAME webkit_mac)
    set(SPECIFIC_OS_FILES
       )
else()
    message(FATAL_ERROR "OS not supported")
endif(Q_WS_X11)

if (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 6)
    set (QtWebKit_46_SRC )
else ()
    set(QtWebKit_46_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebelement_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebelementcollection_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebinspector_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qgraphicswebview_wrapper.cpp
    )
endif (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 6)

set(QtWebKit_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qtwebkit_module_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebdatabase_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebframe_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebhistoryinterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebhistoryitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebhistory_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebhittestresult_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebpage_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebpluginfactory_mimetype_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebpluginfactory_plugin_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebpluginfactory_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebsecurityorigin_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebsettings_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/qwebview_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebKit/webcore_wrapper.cpp

${SPECIFIC_OS_FILES}
${QtWebKit_46_SRC}
)

set(QtWebKit_typesystem_path "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtNetwork_SOURCE_DIR}")
set(QtWebkit_include_dirs   ${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtWebkit/
                            ${QT_INCLUDE_DIR}
                            ${QT_QTCORE_INCLUDE_DIR}
                            ${QT_QTGUI_INCLUDE_DIR}
                            ${QT_QTNETWORK_INCLUDE_DIR}
                            ${QT_QTWEBKIT_INCLUDE_DIR}
                            ${SHIBOKEN_INCLUDE_DIR}
                            ${libpyside_SOURCE_DIR}
                            ${PYTHON_INCLUDE_PATH}
                            ${QtCore_BINARY_DIR}/PySide/QtCore/
                            ${QtGui_BINARY_DIR}/PySide/QtGui/
                            ${QtNetwork_BINARY_DIR}/PySide/QtNetwork/ )
set(QtWebKit_libraries      pyside
                            ${PYSIDE_PYTHON_LIBRARIES}
                            ${SHIBOKEN_LIBRARY}
                            ${QT_QTWEBKIT_LIBRARY}
                            ${QT_QTNETWORK_LIBRARY}
                            ${QT_QTGUI_LIBRARY})
set(QtWebKit_deps QtGui QtNetwork)
create_pyside_module(QtWebKit
                     ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_webkit.xml
                     QtWebkit_include_dirs
                     QtWebKit_libraries
                     QtWebKit_deps
                     QtWebKit_typesystem_path
                     QtWebKit_SRC)

