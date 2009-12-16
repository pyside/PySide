project(libpyside)

set(libpyside_SRC
abstractqobjectconnection.cpp
dynamicqmetaobject.cpp
proxyslot.cpp
signalmanager.cpp
signalsignalconnection.cpp
signalslotconnection.cpp
typeresolver.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    )

add_library(pyside SHARED ${libpyside_SRC})
target_link_libraries(pyside
                      ${PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
)
