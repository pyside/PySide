project(pyside)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py"
        DESTINATION "${SITE_PACKAGE}/${BINDING_NAME}")

macro(execute_generator module sources typesystem_path)
add_custom_command(OUTPUT ${${sources}}
COMMAND ${GENERATOR} ${GENERATOR_EXTRA_FLAGS}
        ${CMAKE_BINARY_DIR}/PySide/global.h
        --include-paths=${pyside_SOURCE_DIR}:${QT_INCLUDE_DIR}
        --typesystem-paths=${pyside_SOURCE_DIR}:${typesystem_path}
        --output-directory=${CMAKE_CURRENT_BINARY_DIR}
        --license-file=${CMAKE_CURRENT_SOURCE_DIR}/../licensecomment.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_${module}.xml
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
COMMENT "Running generator for ${module}..."
)
endmacro(execute_generator)

# Configure include based on platform
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/global.h.in"
               "${CMAKE_CURRENT_BINARY_DIR}/global.h" @ONLY)


# Only add subdirectory if the associated Qt module is found.
macro(HAS_QT_MODULE var name)
if (DISABLE_${name})
    message(STATUS "Generation of ${name} disabled.")
else()
    if (${var})
        add_subdirectory(${name})
        execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_BINARY_DIR}/${name}/${name}${CMAKE_SHARED_MODULE_SUFFIX}"
                                                                "${CMAKE_BINARY_DIR}/PySide/${name}${CMAKE_SHARED_MODULE_SUFFIX}")
    else()
        message(STATUS "${name} NOT found. ${name} support disabled.")
    endif()
endif()
endmacro(HAS_QT_MODULE)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py"
                                                           "${CMAKE_BINARY_DIR}/PySide/__init__.py")
# Try to find QtMultimedia
# TODO: Remove this hack when cmake support QtMultimedia module
if (NOT QT_QTMULTIMEDIA_FOUND AND ${QTVERSION} VERSION_GREATER 4.5.9)
    find_path(QT_QTMULTIMEDIA_INCLUDE_DIR QtMultimedia
            PATHS ${QT_HEADERS_DIR}/QtMultimedia
                ${QT_LIBRARY_DIR}/QtMultimedia.framework/Headers
            NO_DEFAULT_PATH)
    find_library(QT_QTMULTIMEDIA_LIBRARY QtMultimedia PATHS ${QT_LIBRARY_DIR} NO_DEFAULT_PATH)
    if (QT_QTMULTIMEDIA_INCLUDE_DIR AND QT_QTMULTIMEDIA_LIBRARY)
        set(QT_QTMULTIMEDIA_FOUND ON)
    endif()
endif ()

# Try to find QtMaemo5 this need be before QtGui for enable some flags on that
# TODO: Remove this hack when cmake support QtMaemo5 module
if (NOT QT_QTMAEMO5_FOUND AND ${QTVERSION} VERSION_GREATER 4.5.9)
    find_path(QT_QTMAEMO5_INCLUDE_DIR QtMaemo5
            PATHS ${QT_HEADERS_DIR}/QtMaemo5
                ${QT_LIBRARY_DIR}/QtMaemo5.framework/Headers
            NO_DEFAULT_PATH)
    find_library(QT_QTMAEMO5_LIBRARY QtMaemo5 PATHS ${QT_LIBRARY_DIR} NO_DEFAULT_PATH)
    if (QT_QTMAEMO5_INCLUDE_DIR AND QT_QTMAEMO5_LIBRARY)
        set(QT_QTMAEMO5_FOUND ON)
        set(Q_WS_MAEMO_5 ON)
    endif()
endif ()

HAS_QT_MODULE(QT_QTCORE_FOUND QtCore)
HAS_QT_MODULE(QT_QTGUI_FOUND QtGui)
HAS_QT_MODULE(QT_QTNETWORK_FOUND QtNetwork)
HAS_QT_MODULE(QT_QTWEBKIT_FOUND QtWebKit)
HAS_QT_MODULE(QT_QTSVG_FOUND QtSvg)
HAS_QT_MODULE(QT_QTXML_FOUND QtXml)
HAS_QT_MODULE(QT_QTTEST_FOUND QtTest)
HAS_QT_MODULE(QT_QTOPENGL_FOUND QtOpenGL)
HAS_QT_MODULE(QT_QTSQL_FOUND QtSql)
HAS_QT_MODULE(QT_QTUITOOLS_FOUND QtUiTools)
HAS_QT_MODULE(QT_QTHELP_FOUND QtHelp)
HAS_QT_MODULE(QT_QTXMLPATTERNS_FOUND QtXmlPatterns)
HAS_QT_MODULE(QT_QTMAEMO5_FOUND QtMaemo5)
HAS_QT_MODULE(QT_QTSCRIPT_FOUND QtScript)
HAS_QT_MODULE(QT_QTSCRIPTTOOLS_FOUND QtScriptTools)
HAS_QT_MODULE(QT_QTMULTIMEDIA_FOUND QtMultimedia)
HAS_QT_MODULE(QT_PHONON_FOUND phonon)
