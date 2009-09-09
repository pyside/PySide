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

add_subdirectory(QtCore)
