project(QtMultimedia)

set(QtMultimedia_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qaudio_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qabstractvideobuffer_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qabstractvideosurface_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qaudiodeviceinfo_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qaudioformat_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qaudioinput_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qaudiooutput_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qvideoframe_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qvideosurfaceformat_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qtmultimedia_module_wrapper.cpp
)

execute_generator(multimedia QtMultimedia_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/
                    ${QT_INCLUDE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTGUI_INCLUDE_DIR}
                    ${QT_QTMULTIMEDIA_INCLUDE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${QtCore_BINARY_DIR}/PySide/QtCore/
                    ${QtGui_BINARY_DIR}/PySide/QtGui/
                    )

add_library(QtMultimedia MODULE ${QtMultimedia_SRC})
set_property(TARGET QtMultimedia PROPERTY PREFIX "")
target_link_libraries(QtMultimedia
                      pyside
                      ${PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
                      ${QT_QTMULTIMEDIA_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      )
add_dependencies(QtMultimedia QtGui)

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtMultimedia.so
        DESTINATION ${SITE_PACKAGE}/PySide)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/pyside_qtmultimedia_python.h
        DESTINATION include/PySide/QtMultimedia/)
