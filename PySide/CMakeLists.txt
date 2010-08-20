project(pyside)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py"
        DESTINATION "${SITE_PACKAGE}/${BINDING_NAME}")

macro(execute_generator module sources typesystem_path)
    message("Running generator for ${module}...")
endmacro(execute_generator)

macro(create_pyside_module module_name typesystem_file module_include_dir module_libraries module_deps module_typesystem_path module_sources)
    add_custom_command(OUTPUT ${${module_sources}}
                        COMMAND ${GENERATOR} ${GENERATOR_EXTRA_FLAGS}
                        ${CMAKE_BINARY_DIR}/PySide/global.h
                        --include-paths=${pyside_SOURCE_DIR}:${QT_INCLUDE_DIR}
                        --typesystem-paths=${pyside_SOURCE_DIR}:${${module_typesystem_path}}
                        --output-directory=${CMAKE_CURRENT_BINARY_DIR}
                        --license-file=${CMAKE_CURRENT_SOURCE_DIR}/../licensecomment.txt
                        ${typesystem_file}
                        --api-version=${SUPPORTED_QT_VERSION}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        COMMENT "Running generator for ${module_name}...")

    include_directories(${module_name} ${${module_include_dir}})
    add_library(${module_name} MODULE ${${module_sources}})
    set_target_properties(${module_name} PROPERTIES PREFIX "" LIBRARY_OUTPUT_DIRECTORY ${pyside_BINARY_DIR})
    if(WIN32)
        set_target_properties(${module_name} PROPERTIES SUFFIX ".pyd")
    endif()
    target_link_libraries(${module_name} ${${module_libraries}})
    if(${module_deps})
        add_dependencies(${module_name} ${${module_deps}})
    endif()

    # install
    install(FILES ${pyside_BINARY_DIR}/${module_name}${CMAKE_DEBUG_POSTFIX}.so
            DESTINATION ${SITE_PACKAGE}/PySide)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/${module_name}/pyside_${module_name}_python.h
            DESTINATION include/PySide/${module_name}/)
    install(FILES ${typesystem_file}
            DESTINATION share/PySide/typesystems)
endmacro(create_pyside_module)


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
    else()
        message(STATUS "${name} NOT found. ${name} support disabled.")
    endif()
endif()
endmacro(HAS_QT_MODULE)

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py"
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

# Try to find QtMaemo5 - it has to be done before QtGui to enable some QtMaemo5 flags
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

# Try to find QtDeclarative
# TODO: Remove this hack when cmake support QtDeclarative module
if (NOT QT_QTDECLARATIVE_FOUND AND ${QTVERSION} VERSION_GREATER 4.6.0)
    find_path(QT_QTDECLARATIVE_INCLUDE_DIR QtDeclarative
            PATHS ${QT_HEADERS_DIR}/QtDeclarative
                ${QT_LIBRARY_DIR}/QtDeclarative.framework/Headers
            NO_DEFAULT_PATH)
    find_library(QT_QTDECLARATIVE_LIBRARY QtDeclarative PATHS ${QT_LIBRARY_DIR} NO_DEFAULT_PATH)
    if (QT_QTDECLARATIVE_INCLUDE_DIR AND QT_QTDECLARATIVE_LIBRARY)
        set(QT_QTDECLARATIVE_FOUND ON)
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
HAS_QT_MODULE(QT_QTDECLARATIVE_FOUND QtDeclarative)

# install
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_templates.xml
        DESTINATION share/PySide/typesystems)

