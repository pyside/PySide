project(phonon)

# workaround for a cmake bug under MacOSX, it finds phonon but not the include path
if (NOT QT_PHONON_INCLUDE_DIR AND CMAKE_HOST_APPLE)
    set(QT_PHONON_INCLUDE_DIR "${QT_LIBRARY_DIR}/phonon.framework/Headers")
endif()

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
)

execute_generator(phonon phonon_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtGui_SOURCE_DIR}:${phonon_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTGUI_INCLUDE_DIR}
                    ${QT_PHONON_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${QtGui_BINARY_DIR}/PySide/QtGui/
                    ${QtCore_BINARY_DIR}/PySide/QtCore/
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon)
add_library(phonon MODULE ${phonon_SRC})
set_target_properties(phonon PROPERTIES PREFIX "")
target_link_libraries(phonon
                      pyside
                      ${PYSIDE_PYTHON_LIBRARIES}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      ${QT_PHONON_LIBRARY})
add_dependencies(phonon QtGui)

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/phonon${CMAKE_DEBUG_POSTFIX}.so
        DESTINATION ${SITE_PACKAGE}/PySide)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/phonon/pyside_phonon_python.h
        DESTINATION include/PySide/phonon/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_phonon.xml
        DESTINATION share/PySide/typesystems)

