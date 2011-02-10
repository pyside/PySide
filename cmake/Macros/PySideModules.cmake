macro(create_pyside_module module_name module_include_dir module_libraries module_deps module_typesystem_path module_sources typesystem_name)
    string(TOLOWER ${module_name} _module)
    string(REGEX REPLACE ^qt "" _module ${_module})
    if (NOT EXISTS ${typesystem_name})
        set(typesystem_path ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_${_module}.xml)
    else()
        set(typesystem_path ${typesystem_name})
    endif()

    add_custom_command(OUTPUT ${${module_sources}}
                        COMMAND ${GENERATORRUNNER_BINARY} ${GENERATOR_EXTRA_FLAGS}
                        ${pyside_BINARY_DIR}/pyside_global.h
                        --include-paths=${pyside_SOURCE_DIR}${PATH_SEP}${QT_INCLUDE_DIR}
                        --typesystem-paths=${pyside_SOURCE_DIR}${PATH_SEP}${${module_typesystem_path}}
                        --output-directory=${CMAKE_CURRENT_BINARY_DIR}
                        --license-file=${CMAKE_CURRENT_SOURCE_DIR}/../licensecomment.txt
                        ${typesystem_path}
                        --api-version=${SUPPORTED_QT_VERSION}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        COMMENT "Running generator for ${module_name}...")

    include_directories(${module_name} ${${module_include_dir}} ${pyside_SOURCE_DIR})
    add_library(${module_name} MODULE ${${module_sources}} ${${ARGN}})
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
    install(TARGETS ${module_name} LIBRARY DESTINATION ${SITE_PACKAGE}/PySide)
    string(TOLOWER ${module_name} lower_module_name)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/${module_name}/pyside_${lower_module_name}_python.h
            DESTINATION include/PySide${pyside_SUFFIX}/${module_name}/)
    file(GLOB typesystem_files ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_*.xml ${typesystem_path})
    install(FILES ${typesystem_files} DESTINATION share/PySide${pyside_SUFFIX}/typesystems)
endmacro()

macro(append_class_xml commom_xml class_xml)
    INCLUDE(FindPythonInterp)
    set(REPLACE_PROGRAM "import string; \\
                commomFile = open('${commom_xml}', 'r'); \\
                commomData = commomFile.read(); \\
                commomFile.close(); \\
                objectFile = open('${class_xml}', 'r'); \\
                objectData = objectFile.read(); \\
                objectFile.close(); \\
                commomData = string.replace(commomData, '</typesystem>', '%s\\n</typesystem>' % objectData); \\
                commomFile = open('${commom_xml}', 'w'); \\
                commomFile.write(commomData); \\
                commomFile.close();")
    execute_process(
        COMMAND ${PYTHON_EXECUTABLE} -c "${REPLACE_PROGRAM}")
endmacro()

#macro(check_qt_class_with_namespace module namespace class global_sources commom_xml class_xml [namespace] [module])
macro(check_qt_class module class global_sources commom_xml)
    if (${ARGC} GREATER 4)
        set (namespace ${ARGV4})
        string(TOLOWER ${namespace} _namespace)
    else ()
        set (namespace "")
    endif ()
    if (${ARGC} GREATER 5)
        set (include_file ${ARGV5})
    else ()
        set (include_file ${class})
    endif ()
    string(TOLOWER ${class} _class)
    string(TOUPPER ${module} _module)
    if (${namespace})
        set(_cppfile ${CMAKE_CURRENT_BINARY_DIR}/PySide/${module}/${_namespace}_${_class}_wrapper.cpp)
    else ()
        set(_cppfile ${CMAKE_CURRENT_BINARY_DIR}/PySide/${module}/${_class}_wrapper.cpp)
    endif ()
    if (DEFINED PYSIDE_${class})
        if (PYSIDE_${class})
            list(APPEND ${global_sources} ${_cppfile})
        endif()
    else()
        if (NOT ${namespace} STREQUAL "" )
            set (NAMESPACE_USE "using namespace ${namespace};")
        else ()
            set (NAMESPACE_USE "")
        endif ()
        set(SRC_FILE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/test${class}.cxx)
        file(WRITE ${SRC_FILE}
             "#include <${include_file}>\n"
             "${NAMESPACE_USE}\n"
             "int main() { sizeof(${class}); }\n"
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
            append_class_xml(${commom_xml} "${CMAKE_CURRENT_SOURCE_DIR}/optional/${class}.xml")
        else()
            message(STATUS "Checking for ${class} in ${module} -- not found")
        endif()
    endif()
endmacro()


# Only add subdirectory if the associated Qt module is found.
macro(HAS_QT_MODULE var name)
    if (NOT DISABLE_${name} AND ${var})
        add_subdirectory(${name})
    else()
        # Used on documentation to skip modules
        set("if_${name}" "<!--" PARENT_SCOPE)
        set("end_${name}" "-->" PARENT_SCOPE)
    endif()
endmacro()
