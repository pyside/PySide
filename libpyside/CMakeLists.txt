project(libpyside)


qt4_wrap_cpp(DESTROYLISTENER_MOC "destroylistener.h")

set(libpyside_SRC
    dynamicqmetaobject.cpp
    destroylistener.cpp
    signalmanager.cpp
    globalreceiver.cpp
    pysideclassinfo.cpp
    pysidemetafunction.cpp
    pysidesignal.cpp
    pysideslot.cpp
    pysideproperty.cpp
    pysideweakref.cpp
    pyside.cpp
    ${DESTROYLISTENER_MOC}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${SHIBOKEN_PYTHON_INCLUDE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR})
add_library(pyside SHARED ${libpyside_SRC})
target_link_libraries(pyside
                      ${SHIBOKEN_PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
                      ${QT_QTCORE_LIBRARY})

set_target_properties(pyside PROPERTIES
                      VERSION ${BINDING_API_VERSION}
                      SOVERSION "${BINDING_API_MAJOR_VERSION}.${BINDING_API_MINOR_VERSION}"
                      OUTPUT_NAME "pyside${pyside_SUFFIX}-${SHIBOKEN_PYTHON_BASENAME}"
                      DEFINE_SYMBOL PYSIDE_EXPORTS)

#
# install stuff
#

set(libpyside_HEADERS
    destroylistener.h
    dynamicqmetaobject.h
    globalreceiver.h
    pysideclassinfo.h
    pysideconversions.h
    pysidemacros.h
    signalmanager.h
    pyside.h
    pysidemetafunction.h
    pysidesignal.h
    pysideproperty.h
    pysideweakref.h
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIBRARY_OUTPUT_SUFFIX ${CMAKE_DEBUG_POSTFIX})
else()
    set(LIBRARY_OUTPUT_SUFFIX ${CMAKE_RELEASE_POSTFIX})
endif()

# create pkg-config file
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/pyside.pc.in"
               "${CMAKE_CURRENT_BINARY_DIR}/pyside${pyside_SUFFIX}.pc" @ONLY)
# create cmake-config files
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/PySideConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/PySideConfig.cmake" @ONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/PySideConfig-spec.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/PySideConfig-${SHIBOKEN_PYTHON_BASENAME}.cmake" @ONLY)
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
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/PySideConfig-${SHIBOKEN_PYTHON_BASENAME}.cmake"
        DESTINATION "${LIB_INSTALL_DIR}/cmake/PySide-${BINDING_API_VERSION}")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/PySideConfigVersion.cmake"
        DESTINATION "${LIB_INSTALL_DIR}/cmake/PySide-${BINDING_API_VERSION}")
