project(pyside)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py"
        DESTINATION "${SITE_PACKAGE}/${BINDING_NAME}")

macro(execute_generator module sources typesystem_path)
add_custom_command(OUTPUT ${${sources}}
COMMAND ${GENERATOR} ${GENERATOR_EXTRA_FLAGS}
        ${pyside_SOURCE_DIR}/global.h
        --include-paths=${pyside_SOURCE_DIR}:${QT_INCLUDE_DIR}
        --typesystem-paths=${pyside_SOURCE_DIR}:${typesystem_path}
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
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_BINARY_DIR}/${name}/${name}${CMAKE_SHARED_MODULE_SUFFIX}"
                                                               "${CMAKE_BINARY_DIR}/PySide/${name}${CMAKE_SHARED_MODULE_SUFFIX}")
else()
    message(STATUS "${name} NOT found. ${name} support disabled.")
endif()
endmacro(HAS_QT_MODULE)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py"
                                                           "${CMAKE_BINARY_DIR}/PySide/__init__.py")

HAS_QT_MODULE(QT_QTCORE_FOUND QtCore)
HAS_QT_MODULE(QT_QTGUI_FOUND QtGui)
HAS_QT_MODULE(QT_QTNETWORK_FOUND QtNetwork)
HAS_QT_MODULE(QT_QTWEBKIT_FOUND QtWebKit)
HAS_QT_MODULE(QT_QTSVG_FOUND QtSvg)
HAS_QT_MODULE(QT_QTXML_FOUND QtXml)
HAS_QT_MODULE(QT_QTTEST_FOUND QtTest)
HAS_QT_MODULE(QT_QTOPENGL_FOUND QtOpenGL)
HAS_QT_MODULE(QT_QTSQL_FOUND QtSql)
