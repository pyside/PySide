project(doc)

set(DOC_DATA_DIR "${CMAKE_CURRENT_BINARY_DIR}/qdoc3-output")
configure_file("pyside.qdocconf.in" "pyside.qdocconf" @ONLY)

add_custom_target(qdoc3
                COMMAND qdoc3 pyside.qdocconf
                COMMENT "Running qdoc3 against Qt source code..."
                SOURCE "pyside.qdocconf")

add_custom_target(apidoc
                  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/rst
                  COMMAND sphinx-build -b html  ${CMAKE_CURRENT_BINARY_DIR}/rst html
                 )

# create conf.py based on conf.py.in
configure_file("conf.py.in" "rst/conf.py" @ONLY)
configure_file(typesystem_doc.xml.in typesystem_doc.xml @ONLY)

add_custom_target("docrsts"
    COMMAND ${GENERATORRUNNER_BINARY} --generator-set=qtdoc
            ${pyside_BINARY_DIR}/pyside_global.h
            --include-paths="${QT_INCLUDE_DIR}${PATH_SEP}${pyside_SOURCE_DIR}"
            --api-version=${SUPPORTED_QT_VERSION}
            --typesystem-paths="${pyside_SOURCE_DIR}${PATH_SEP}${QtCore_SOURCE_DIR}${PATH_SEP}${QtDeclarative_SOURCE_DIR}${PATH_SEP}${QtGui_SOURCE_DIR}${PATH_SEP}${QtGui_BINARY_DIR}${PATH_SEP}${QtHelp_SOURCE_DIR}${PATH_SEP}${QtMaemo5_SOURCE_DIR}${PATH_SEP}${QtMultimedia_SOURCE_DIR}${PATH_SEP}${QtNetwork_SOURCE_DIR}${PATH_SEP}${QtOpenGL_SOURCE_DIR}${PATH_SEP}${QtScript_SOURCE_DIR}${PATH_SEP}${QtScriptTools_SOURCE_DIR}${PATH_SEP}${QtSql_SOURCE_DIR}${PATH_SEP}${QtSvg_SOURCE_DIR}${PATH_SEP}${QtTest_SOURCE_DIR}${PATH_SEP}${QtUiTools_SOURCE_DIR}${PATH_SEP}${QtWebKit_SOURCE_DIR}${PATH_SEP}${QtXml_SOURCE_DIR}${PATH_SEP}${QtXmlPatterns_SOURCE_DIR}${PATH_SEP}${phonon_SOURCE_DIR}"
            --library-source-dir=${QT_SRC_DIR}
            --documentation-only
            --documentation-data-dir=${DOC_DATA_DIR}
            --output-directory=${CMAKE_CURRENT_BINARY_DIR}/rst
            --documentation-code-snippets-dir=${CMAKE_CURRENT_SOURCE_DIR}/codesnippets
            --documentation-extra-sections-dir=${CMAKE_CURRENT_SOURCE_DIR}/extras
            ${CMAKE_CURRENT_BINARY_DIR}/typesystem_doc.xml
    WORKING_DIRECTORY ${${module}_SOURCE_DIR}
    COMMENT "Running generator to generate documentation..."
)
add_dependencies(apidoc docrsts)
add_dependencies(docrsts qdoc3)

# #create devhelp file
# add_custom_target(apidevhelp
#     COMMAND python;${CMAKE_CURRENT_SOURCE_DIR}/pyhtml2devhelp.py;${CMAKE_BINARY_DIR}/apidoc/html;index.html >
#             ${CMAKE_BINARY_DIR}/apidoc/html/PySide.devhelp;${BINDING_API_VERSION}&&;
#             gzip;-9v;-f;${CMAKE_BINARY_DIR}/apidoc/html/PySide.devhelp
#     COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_INSTALL_PREFIX}/share/devhelp/books"
#     COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_INSTALL_PREFIX}/share/doc/${BINDING_NAME}/html" "${CMAKE_INSTALL_PREFIX}/share/devhelp/books/${BINDING_NAME}"
# )

#install files
add_custom_target(apidocinstall
    COMMAND mkdir -p ${CMAKE_INSTALL_PREFIX}/share/doc/PySide-${BINDING_API_VERSION} && cp -rv ${CMAKE_CURRENT_BINARY_DIR}/html/* ${CMAKE_INSTALL_PREFIX}/share/doc/PySide-${BINDING_API_VERSION}
)

add_dependencies(apidocinstall apidoc)
# add_dependencies(apidocinstall apidevhelp)

