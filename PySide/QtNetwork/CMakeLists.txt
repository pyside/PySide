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

if (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 6)
    set (QtNetwork_46_SRC )
else (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 6)
    set(QtNetwork_46_SRC
       )
endif (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 6)

set(QtNetwork_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qabstractsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qauthenticator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qftp_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qhostaddress_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qhostinfo_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qhttpheader_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qhttprequestheader_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qhttpresponseheader_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qhttp_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qipv6address_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qlocalserver_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qlocalsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkaccessmanager_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkaddressentry_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkcookiejar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkcookie_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkinterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkproxy_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkreply_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qnetworkrequest_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qsslcipher_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qsslconfiguration_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qsslerror_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qsslkey_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qsslsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qssl_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qtcpserver_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qtcpsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qtnetwork_module_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qudpsocket_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/qurlinfo_wrapper.cpp
${SPECIFIC_OS_FILES}
${QtNetwork_46_SRC}
)

execute_generator(network QtNetwork_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtNetwork/
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
        DESTINATION ${SITE_PACKAGE}/PySide)
