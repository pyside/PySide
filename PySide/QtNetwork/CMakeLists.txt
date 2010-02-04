project(QtNetwork)

# Check QtNetwork support
macro(CHECK_QT_NETWORK_MACRO macro_display_name qt_macro module_sources global_sources)
    if (DEFINED PYSIDE_${qt_macro})
        if (PYSIDE_${qt_macro})
            list(APPEND ${global_sources} ${${module_sources}})
        endif()
    else()
        set(SRC_FILE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/test${qt_macro}.cxx)
        file(WRITE ${SRC_FILE}
        "#include <QtNetwork>\n"
        "int main() { \n"
        "#ifdef ${qt_macro}\n"
        "#error not supported.\n"
        "#endif\n"
        "}\n")

        try_compile(Q_WORKS ${CMAKE_BINARY_DIR}
                    ${SRC_FILE}
                    CMAKE_FLAGS
                    -DINCLUDE_DIRECTORIES:STRING=${QT_QTNETWORK_INCLUDE_DIR}\;${QT_INCLUDE_DIR}
                    -DLINK_LIBRARIES:PATH=${QT_QTNETWORK_LIBRARY_RELEASE}
                    OUTPUT_VARIABLE OUTPUT)

        set("PYSIDE_${qt_macro}" ${Q_WORKS} CACHE STRING "Has this Qt module been found by pyside?")
        if(Q_WORKS)
            message(STATUS "Testing support to ${macro_display_name} -- enabled")
            list(APPEND ${global_sources} ${${module_sources}})
        else()
            message(STATUS "Testing support to ${macro_display_name} -- disabled")
        endif()
    endif()
endmacro(CHECK_QT_NETWORK_MACRO)


if(Q_WS_X11)
    set(MODULE_NAME network_x11)
    set(SPECIFIC_OS_FILES
       )

elseif(Q_WS_MAC)
    set(MODULE_NAME network_mac)
    set(SPECIFIC_OS_FILES
       )
else(Q_WS_MAC)
    message(FATAL_ERROR "OS not supported")
endif(Q_WS_X11)

if ((${QT_VERSION_MAJOR} EQUAL 4) AND (${QT_VERSION_MINOR} LESS 6))
    set (QtNetwork_46_SRC )
else ((${QT_VERSION_MAJOR} EQUAL 4) AND (${QT_VERSION_MINOR} LESS 6))
    set(QtNetwork_46_SRC
       )
endif ((${QT_VERSION_MAJOR} EQUAL 4) AND (${QT_VERSION_MINOR} LESS 6))

set(QtNetwork_SRC
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/converter_register_qtnetwork.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qabstractsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qabstractsocket_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qauthenticator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qauthenticator_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qftp_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qftp_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qhostaddress_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qhostaddress_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qhostinfo_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qhostinfo_wrapper.hpp
# Obsoletes since Qt 4.6
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qhttpheader_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qhttpheader_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qhttprequestheader_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qhttprequestheader_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qhttpresponseheader_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qhttpresponseheader_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qhttp_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qhttp_wrapper.hpp
# End of obsoletes since Qt 4.6
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qipv6address_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qipv6address_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qlocalserver_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qlocalserver_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qlocalsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qlocalsocket_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkaccessmanager_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkaccessmanager_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkaddressentry_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkaddressentry_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkcookiejar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkcookiejar_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkcookie_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkcookie_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkinterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkinterface_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkproxy_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkproxy_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkreply_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkreply_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkrequest_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qnetworkrequest_wrapper.hpp
#${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qsslcertificate_wrapper.cpp
#${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qsslcertificate_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qsslcipher_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qsslcipher_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qsslconfiguration_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qsslconfiguration_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qsslerror_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qsslerror_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qsslkey_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qsslkey_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qsslsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qsslsocket_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qssl_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qssl_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qtcpserver_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qtcpserver_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qtcpsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qtcpsocket_wrapper.hpp
#${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qtnetwork_globals_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qtnetwork_module_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qudpsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qudpsocket_wrapper.hpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qurlinfo_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/qurlinfo_wrapper.hpp

${SPECIFIC_OS_FILES}
${QtNetwork_46_SRC}
)

execute_generator(network QtNetwork_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}/${BINDING_NAME}/QtNetwork/
                    ${QT_INCLUDE_DIR}
                    ${QT_QTNETWORK_INCLUDE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${QtCore_BINARY_DIR}/PySide/QtCore/
                    )

add_library(QtNetwork SHARED ${QtNetwork_SRC})
set_property(TARGET QtNetwork PROPERTY PREFIX "")
target_link_libraries(QtNetwork
                      pyside
                      QtCore
                      ${PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
                      ${QT_QTNETWORK_LIBRARY}
                      )

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtNetwork.so
        DESTINATION ${SITE_PACKAGE}/${BINDING_NAME})
