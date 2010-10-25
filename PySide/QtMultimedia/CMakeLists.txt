project(QtMultimedia)

set(QtMultimedia_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qaudio_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qabstractvideobuffer_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qaudioenginefactoryinterface_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qvideosurfaceformat_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qabstractvideosurface_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qaudiodeviceinfo_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qabstractaudiodeviceinfo_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qabstractaudiooutput_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qabstractaudioinput_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qaudioengineplugin_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qaudioformat_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qaudioinput_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qaudiooutput_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qvideoframe_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/qtmultimedia_module_wrapper.cpp
)
set(QtMultimedia_typesystem_path "${QtCore_SOURCE_DIR}${PATH_SEP}${QtGui_SOURCE_DIR}${PATH_SEP}${QtGui_BINARY_DIR}")

set(QtMultimedia_include_dirs   ${CMAKE_CURRENT_SOURCE_DIR}
                                ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtMultimedia/
                                ${QT_INCLUDE_DIR}
                                ${QT_QTCORE_INCLUDE_DIR}
                                ${QT_QTGUI_INCLUDE_DIR}
                                ${QT_QTMULTIMEDIA_INCLUDE_DIR}
                                ${SHIBOKEN_INCLUDE_DIR}
                                ${libpyside_SOURCE_DIR}
                                ${PYTHON_INCLUDE_PATH}
                                ${QtCore_BINARY_DIR}/PySide/QtCore/
                                ${QtGui_BINARY_DIR}/PySide/QtGui/)

set(QtMultimedia_libraries  pyside
                            ${SHIBOKEN_PYTHON_LIBRARIES}
                            ${SHIBOKEN_LIBRARY}
                            ${QT_QTMULTIMEDIA_LIBRARY}
                            ${QT_QTGUI_LIBRARY})

set(QtMultimedia_deps QtGui)

create_pyside_module(QtMultimedia
                     QtMultimedia_include_dirs
                     QtMultimedia_libraries
                     QtMultimedia_deps
                     QtMultimedia_typesystem_path
                     QtMultimedia_SRC
                     "")
