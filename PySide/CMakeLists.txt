project(pyside)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py"
        DESTINATION "${SITE_PACKAGE}/${BINDING_NAME}")

macro(execute_generator module sources typesystem_path)
    message("Running generator for ${module}...")
endmacro()

macro(create_pyside_module module_name module_include_dir module_libraries module_deps module_typesystem_path module_sources typesystem_name)
    string(TOLOWER ${module_name} _module)
    string(REGEX REPLACE ^qt "" _module ${_module})
    if (NOT EXISTS ${typesystem_name})
        set(typesystem_path ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_${_module}.xml)
    else()
        set(typesystem_path ${typesystem_name})
    endif()

    add_custom_command(OUTPUT ${${module_sources}}
                        COMMAND ${GENERATOR} ${GENERATOR_EXTRA_FLAGS}
                        ${CMAKE_BINARY_DIR}/PySide/global.h
                        --include-paths=${pyside_SOURCE_DIR}${PATH_SEP}${QT_INCLUDE_DIR}
                        --typesystem-paths=${pyside_SOURCE_DIR}${PATH_SEP}${${module_typesystem_path}}
                        --output-directory=${CMAKE_CURRENT_BINARY_DIR}
                        --license-file=${CMAKE_CURRENT_SOURCE_DIR}/../licensecomment.txt
                        ${typesystem_path}
                        --api-version=${SUPPORTED_QT_VERSION}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        COMMENT "Running generator for ${module_name}...")

    include_directories(${module_name} ${${module_include_dir}})
    add_library(${module_name} MODULE ${${module_sources}})
    set_target_properties(${module_name} PROPERTIES PREFIX "" LIBRARY_OUTPUT_DIRECTORY ${pyside_BINARY_DIR})
    if(WIN32)
        set_target_properties(${module_name} PROPERTIES SUFFIX ".pyd")
        set(${module_name}_suffix ".pyd")
    else()
        set(${module_name}_suffix ".so")
    endif()
    target_link_libraries(${module_name} ${${module_libraries}})
    if(${module_deps})
        add_dependencies(${module_name} ${${module_deps}})
    endif()


    # install
    install(FILES ${pyside_BINARY_DIR}/${module_name}${CMAKE_DEBUG_POSTFIX}${${module_name}_suffix}
            DESTINATION ${SITE_PACKAGE}/PySide)
    string(TOLOWER ${module_name} lower_module_name)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/${module_name}/pyside_${lower_module_name}_python.h
            DESTINATION include/PySide/${module_name}/)
    file(GLOB typesystem_files ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_*.xml)
    install(FILES ${typesystem_files} DESTINATION share/PySide/typesystems)
endmacro()

macro(check_qt_class module class global_sources)
    string(TOLOWER ${class} _class)
    string(TOUPPER ${module} _module)
    set(_cppfile ${CMAKE_CURRENT_BINARY_DIR}/PySide/${module}/${_class}_wrapper.cpp)
    if (DEFINED PYSIDE_${class})
        if (PYSIDE_${class})
            list(APPEND ${global_sources} ${_cppfile})
        endif()
    else()
        set(SRC_FILE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/test${class}.cxx)
        file(WRITE ${SRC_FILE}
             "#include <${module}>\n"
             "#include <typeinfo>\n"
             "int main() { typeid(${class}); }\n"
        )
        try_compile(Q_WORKS ${CMAKE_BINARY_DIR}
                    ${SRC_FILE}
                    CMAKE_FLAGS
                        "-DLINK_LIBRARIES=${QT_${_module}_LIBRARY}"
                        "-DLINK_DIRECTORIES=${QT_LIBRARY_DIR}"
                        "-DINCLUDE_DIRECTORIES=${QT_INCLUDE_DIR};${QT_${_module}_INCLUDE_DIR}"
                    OUTPUT_VARIABLE OUTPUT)
        file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeCheckQtClassTest.log ${OUTPUT})

        set("PYSIDE_${class}" ${Q_WORKS} CACHE STRING "Has ${class} class been found?")
        if(Q_WORKS)
            message(STATUS "Checking for ${class} in ${module} -- found")
            list(APPEND ${global_sources} ${_cppfile})
        else()
            message(STATUS "Checking for ${class} in ${module} -- not found")
        endif()
    endif()
endmacro()

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
endmacro()

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

