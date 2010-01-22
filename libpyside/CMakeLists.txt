project(libpyside)

set(libpyside_SRC
dynamicqmetaobject.cpp
signalmanager.cpp
globalreceiver.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${QT_QTCORE_INCLUDE_DIR})

add_library(pyside SHARED ${libpyside_SRC})
target_link_libraries(pyside
                      ${PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
                      ${QT_QTCORE_LIBRARY})

set_target_properties(pyside PROPERTIES
                      VERSION ${BINDING_API_VERSION}
                      SOVERSION ${BINDING_API_MAJOR_VERSION})

#
# install stuff
#

set(libpyside_HEADERS
    dynamicqmetaobject.h
    globalreceiver.h
    pysidemacros.h
    signalmanager.h
)

install(FILES ${libpyside_HEADERS}
        DESTINATION include/${BINDING_NAME})
install(TARGETS pyside LIBRARY DESTINATION ${LIB_INSTALL_DIR})
