project(plugins)

set(ui_plugin_src
    customwidgets.cpp
    customwidget.cpp
)

set(ui_plugin_moc
    customwidget.h
    customwidgets.h
)

include_directories(${QT_QTDESIGNER_INCLUDE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${SHIBOKEN_PYTHON_INCLUDE_DIR})

QT4_WRAP_CPP(MOC_FILES ${ui_plugin_moc})
add_library(uiplugin STATIC ${ui_plugin_src} ${MOC_FILES})
add_definitions(-fPIC)
add_definitions(-DQT_STATICPLUGIN)
target_link_libraries(uiplugin
                      ${QT_QTUITOOLS_LIBRARY}
                      ${SHIBOKEN_LIBRARY}
                      ${SHIBOKEN_PYTHON_LIBRARY})
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIBRARY_OUTPUT_SUFFIX ${CMAKE_DEBUG_POSTFIX})
else()
    set(LIBRARY_OUTPUT_SUFFIX ${CMAKE_RELEASE_POSTFIX})
endif()
