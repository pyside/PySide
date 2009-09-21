macro(execute_generator module sources)
add_custom_command(OUTPUT ${${sources}}
COMMAND ${GENERATOR} ${GENERATOR_EXTRA_FLAGS}
        ${CMAKE_CURRENT_SOURCE_DIR}/../global.h
        --include-paths=${QT_INCLUDE_DIR}
        --typesystem-paths=${typesystem_SOURCE_DIR}
        --output-directory=${CMAKE_CURRENT_BINARY_DIR}
        --license-file=${CMAKE_CURRENT_SOURCE_DIR}/../licensecomment.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_${module}.xml
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
COMMENT "Running generator for ${module}..."
)
endmacro(execute_generator)

# Only add subdirectory if the associated Qt module is found.
macro(HAS_QT_MODULE var name)
IF (${var})
    add_subdirectory(${name})
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_BINARY_DIR}/${name}/${name}.so"
                                                               "${CMAKE_BINARY_DIR}/PySide/${name}.so")
else (${var})
    message(STATUS "${name} NOT found. ${name} support disabled.")
endif (${var})
endmacro(HAS_QT_MODULE)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py"
                                                           "${CMAKE_BINARY_DIR}/PySide/__init__.py")

HAS_QT_MODULE(QT_QTCORE_FOUND QtCore)
