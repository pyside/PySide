project(phonon)

# workaround for a cmake bug under MacOSX, it finds phonon but not the include path
if (NOT QT_PHONON_INCLUDE_DIR AND CMAKE_HOST_APPLE)
    set(QT_PHONON_INCLUDE_DIR "${QT_LIBRARY_DIR}/phonon.framework/Headers")
endif ()

set(phonon_OPTIONAL_SRC )
set(phonon_DROPPED_ENTRIES )
check_qt_class(phonon VideoCaptureDevice    phonon_OPTIONAL_SRC phonon_DROPPED_ENTRIES Phonon ObjectDescription)

set(phonon_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_abstractaudiooutput_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_abstractmediastream_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_abstractvideooutput_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_addoninterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_audiocapturedevice_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_audiochanneldescription_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_audiooutputdevicemodel_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_audiooutputdevice_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_audiooutput_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_backendcapabilities_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_backendinterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_effectdescriptionmodel_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_effectdescription_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_effectinterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_effectparameter_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_effectwidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_effect_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_mediacontroller_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_medianode_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_mediaobjectinterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_mediaobject_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_mediasource_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_module_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_path_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_platformplugin_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_seekslider_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_streaminterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_subtitledescription_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_videoplayer_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_videowidgetinterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_videowidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_volumefadereffect_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_volumefaderinterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_volumeslider_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/phonon_backendcapabilities_notifierwrapper_wrapper.cpp
${phonon_OPTIONAL_SRC}
)

set(phonon_typesystem_path "${QtCore_SOURCE_DIR}${PATH_SEP}${QtGui_SOURCE_DIR}${PATH_SEP}${phonon_SOURCE_DIR}${PATH_SEP}${QtGui_BINARY_DIR}")
set(phonon_include_dirs ${CMAKE_CURRENT_SOURCE_DIR}
                        ${QT_QTCORE_INCLUDE_DIR}
                        ${QT_QTGUI_INCLUDE_DIR}
                        ${QT_PHONON_INCLUDE_DIR}
                        ${SHIBOKEN_PYTHON_INCLUDE_DIR}
                        ${SHIBOKEN_INCLUDE_DIR}
                        ${libpyside_SOURCE_DIR}
                        ${QtGui_BINARY_DIR}/PySide/QtGui/
                        ${QtCore_BINARY_DIR}/PySide/QtCore/
                        ${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon)
set(phonon_libraries  pyside
                      ${SHIBOKEN_PYTHON_LIBRARIES}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      ${QT_PHONON_LIBRARY})
set(phonon_deps QtGui)

create_pyside_module(phonon
                     phonon_include_dirs
                     phonon_libraries
                     phonon_deps
                     phonon_typesystem_path
                     phonon_SRC
                     ""
                     phonon_DROPPED_ENTRIES)
