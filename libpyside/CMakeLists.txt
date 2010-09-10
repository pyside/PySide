project(libpyside)

set(libpyside_SRC
dynamicqmetaobject.cpp
signalmanager.cpp
globalreceiver.cpp
qsignal.cpp
qslot.cpp
qproperty.cpp
pyside.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${QT_QTCORE_INCLUDE_DIR})

add_library(pyside SHARED ${libpyside_SRC})
target_link_libraries(pyside
                      ${PYSIDE_PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
                      ${QT_QTCORE_LIBRARY})

set_target_properties(pyside PROPERTIES
                      VERSION ${BINDING_API_VERSION}
                      SOVERSION "${BINDING_API_MAJOR_VERSION}.${BINDING_API_MINOR_VERSION}"
                      OUTPUT_NAME "pyside${pyside_SUFFIX}"
                      DEFINE_SYMBOL PYSIDE_EXPORTS)

#
# install stuff
#

set(libpyside_HEADERS
    dynamicqmetaobject.h
    globalreceiver.h
    pysideconversions.h
    pysidemacros.h
    signalmanager.h
    pyside.h
    qsignal.h
    qproperty.h
)

# create pkg-config file
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/pyside.pc.in"
               "${CMAKE_CURRENT_BINARY_DIR}/pyside${pyside_SUFFIX}.pc" @ONLY)
# create cmake-config files
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/PySideConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/PySideConfig.cmake" @ONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/PySideConfigVersion.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/PySideConfigVersion.cmake" @ONLY)

install(FILES ${libpyside_HEADERS}
        DESTINATION include/${BINDING_NAME}${pyside_SUFFIX})
install(TARGETS pyside EXPORT pyside
                       LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                       ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                       RUNTIME DESTINATION bin)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pyside${pyside_SUFFIX}.pc" DESTINATION "${LIB_INSTALL_DIR}/pkgconfig")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/PySideConfig.cmake"
        DESTINATION "${LIB_INSTALL_DIR}/cmake/PySide-${BINDING_API_VERSION}")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/PySideConfigVersion.cmake"
        DESTINATION "${LIB_INSTALL_DIR}/cmake/PySide-${BINDING_API_VERSION}")
