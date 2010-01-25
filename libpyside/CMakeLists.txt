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
