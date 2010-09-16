find_program(graphviz_exec dot)

if (QT_SRC_DIR)

if (NOT ${graphviz_exec} STREQUAL graphviz_exec-NOTFOUND)

add_custom_target(apidoc
                  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/rst
                  COMMAND sphinx-build -b html  ${CMAKE_CURRENT_BINARY_DIR}/rst htmldocs
                 )

# create conf.py based on conf.py.in
configure_file("conf.py.in" "rst/conf.py" @ONLY)

# copy pyside.qdocconf to qt source dir.
configure_file("pyside.qdocconf" "${QT_SRC_DIR}/tools/qdoc3/test/pyside.qdocconf" @ONLY)
set(DOC_DATA_DIR "${CMAKE_CURRENT_BINARY_DIR}/qt4xmldoc")
set(ENV{QTDIR} ${QT_SRC_DIR} )

add_custom_target(qdoc3
                  COMMAND QTDIR=${QT_SRC_DIR} qdoc3 pyside.qdocconf
                  WORKING_DIRECTORY "${QT_SRC_DIR}/tools/qdoc3/test"
                  COMMENT "Running qdoc3 against Qt source code..."
                  SOURCE "pyside.qdocconf")

macro(create_doc module typesystem_path)
string(REGEX REPLACE "^Qt" "" module_name ${module})
string(TOLOWER ${module_name} module_name)
add_custom_target("${module}-apidoc"
COMMAND ${GENERATORRUNNER_BINARY} --generatorSet=qtdoc
        ${pyside_BINARY_DIR}/global.h
        --include-paths=${QT_INCLUDE_DIR}:${QT_QTCORE_INCLUDE_DIR}
        --typesystem-paths=${pyside_SOURCE_DIR}:${${module}_BINARY_DIR}:${typesystem_path}
        ${pyside_SOURCE_DIR}/${module}/typesystem_${module_name}.xml
        --library-source-dir=${QT_SRC_DIR}
        --documentation-only
        --documentation-data-dir=${DOC_DATA_DIR}
        --documentation-out-dir=${CMAKE_CURRENT_BINARY_DIR}/rst
        --documentation-code-snippets-dir=${CMAKE_CURRENT_SOURCE_DIR}/codesnippets
WORKING_DIRECTORY ${${module}_SOURCE_DIR}

COMMENT "Running generator to generate documentation of ${module}..."
)
add_dependencies("${module}-apidoc" qdoc3)
add_dependencies(apidoc "${module}-apidoc")
endmacro()

create_doc(QtCore "")
create_doc(QtGui "${QtCore_SOURCE_DIR}")
create_doc(QtHelp "${QtCore_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtGui_SOURCE_DIR}:${QtHelp_SOURCE_DIR}")
create_doc(QtNetwork "${QtCore_SOURCE_DIR}")
create_doc(QtOpengl "${QtCore_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtGui_SOURCE_DIR}:${QtOpenGL_SOURCE_DIR}")
create_doc(QtSql "${QtCore_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtGui_SOURCE_DIR}:${QtSql_SOURCE_DIR}")
create_doc(QtSvg "${QtCore_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}")
create_doc(QtUitools "${QtCore_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtGui_SOURCE_DIR}:${QtXml_SOURCE_DIR}:${QtUiTools_SOURCE_DIR}")
create_doc(QtXml "${QtCore_SOURCE_DIR}")
create_doc(QtWebKit "${QtCore_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtNetwork_SOURCE_DIR}")
create_doc(QtMultimedia "${QtCore_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}")
create_doc(QtScript "${QtCore_SOURCE_DIR}")
create_doc(QtScriptTools "${QtCore_SOURCE_DIR}:${QtScript_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}")
create_doc(QtTest "${QtCore_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}")
create_doc(QtXmlPatterns "${QtCore_SOURCE_DIR}")
create_doc(phonon "${QtCore_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}")
if (QT_QTDECLARATIVE_FOUND)
    create_doc(QtDeclarative "${QtCore_SOURCE_DIR}:${QtGui_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtNetwork_SOURCE_DIR}")
endif()

#create devhelp file
add_custom_target(apidevhelp
    COMMAND python;${CMAKE_CURRENT_SOURCE_DIR}/pyhtml2devhelp.py;${CMAKE_BINARY_DIR}/apidoc/html;index.html >
            ${CMAKE_BINARY_DIR}/apidoc/html/PySide.devhelp;${BINDING_API_VERSION}&&;
            gzip;-9v;-f;${CMAKE_BINARY_DIR}/apidoc/html/PySide.devhelp
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_INSTALL_PREFIX}/share/devhelp/books"
    COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_INSTALL_PREFIX}/share/doc/${BINDING_NAME}/html" "${CMAKE_INSTALL_PREFIX}/share/devhelp/books/${BINDING_NAME}"
)

#install files
add_custom_target(apidocinstall
    COMMAND mkdir -p ${CMAKE_INSTALL_PREFIX}/share/doc/${BINDING_NAME} && cp -rv ${CMAKE_BINARY_DIR}/apidoc/* ${CMAKE_INSTALL_PREFIX}/share/doc/${BINDING_NAME}
)

add_dependencies(apidocinstall apidevhelp)

else ()
    message(STATUS "Missing graphviz tool (dot), apidoc generation targets disabled.")
endif ()

else ()
    message(STATUS "QT_SRC_DIR variable not set, apidoc generation targets disabled.")
endif ()

