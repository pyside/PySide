project(QtNetwork)

if (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} GREATER 6)
    set (QtNetwork_47_SRC
        ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkconfiguration_wrapper.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkconfigurationmanager_wrapper.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworksession_wrapper.cpp
    )
else()
    set(QtNetwork_47_SRC )
endif ()

set(QtNetwork_OPTIONAL_SRC )
set(QtNetwork_DROPPED_ENTRIES )
check_qt_class(QtNetwork QSslCertificate    QtNetwork_OPTIONAL_SRC QtNetwork_DROPPED_ENTRIES)
check_qt_class(QtNetwork QSslCipher         QtNetwork_OPTIONAL_SRC QtNetwork_DROPPED_ENTRIES)
check_qt_class(QtNetwork QSslConfiguration  QtNetwork_OPTIONAL_SRC QtNetwork_DROPPED_ENTRIES)
check_qt_class(QtNetwork QSslError          QtNetwork_OPTIONAL_SRC QtNetwork_DROPPED_ENTRIES)
check_qt_class(QtNetwork QSslKey            QtNetwork_OPTIONAL_SRC QtNetwork_DROPPED_ENTRIES)
check_qt_class(QtNetwork QSslSocket         QtNetwork_OPTIONAL_SRC QtNetwork_DROPPED_ENTRIES)

set(QtNetwork_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qabstractnetworkcache_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qabstractsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qauthenticator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qftp_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qhostaddress_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qhostinfo_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qhttp_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qhttpheader_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qhttprequestheader_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qhttpresponseheader_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qipv6address_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qlocalserver_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qlocalsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkaccessmanager_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkaddressentry_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkcachemetadata_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkcookie_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkcookiejar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkdiskcache_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkinterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkproxy_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkproxyfactory_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkproxyquery_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkreply_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkrequest_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qssl_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qtcpserver_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qtcpsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qtnetwork_module_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qudpsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qurlinfo_wrapper.cpp

${QtNetwork_47_SRC}
${QtNetwork_OPTIONAL_SRC}
)

set(QtNetwork_typesystem_path "${QtCore_SOURCE_DIR}${PATH_SEP}${QtCore_BINARY_DIR}")
set(QtNetwork_include_dirs  ${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/
                            ${QT_INCLUDE_DIR}
                            ${QT_QTNETWORK_INCLUDE_DIR}
                            ${SHIBOKEN_INCLUDE_DIR}
                            ${libpyside_SOURCE_DIR}
                            ${SHIBOKEN_PYTHON_INCLUDE_DIR}
                            ${QtCore_BINARY_DIR}/PySide/QtCore/)
set(QtNetwork_libraries pyside
                        ${SHIBOKEN_PYTHON_LIBRARIES}
                        ${SHIBOKEN_LIBRARY}
                        ${QT_QTNETWORK_LIBRARY})

set(QtNetwork_deps QtCore)

create_pyside_module(QtNetwork
                     QtNetwork_include_dirs
                     QtNetwork_libraries
                     QtNetwork_deps
                     QtNetwork_typesystem_path
                     QtNetwork_SRC
                     ""
                     ""
                     QtNetwork_DROPPED_ENTRIES)
