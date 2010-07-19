project(QtSql)

set(QtSql_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqlindex_wrapper.cpp

    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqldatabase_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqldrivercreatorbase_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqldriver_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqlerror_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqlfield_wrapper.cpp

    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqlquerymodel_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqlquery_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqlrecord_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqlrelationaldelegate_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqlrelationaltablemodel_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqlrelation_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqlresult_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsqltablemodel_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qsql_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/qtsql_module_wrapper.cpp
)

execute_generator(sql QtSql_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}:${QtGui_BINARY_DIR}:${QtGui_SOURCE_DIR}:${QtSql_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTGUI_INCLUDE_DIR}
                    ${QT_QTSQL_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${QtCore_BINARY_DIR}/PySide/QtCore/
                    ${QtGui_BINARY_DIR}/PySide/QtGui/
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/)
add_library(QtSql MODULE ${QtSql_SRC})
set_target_properties(QtSql PROPERTIES PREFIX "")
target_link_libraries(QtSql
                      pyside
                      ${PYSIDE_PYTHON_LIBRARIES}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      ${QT_QTSQL_LIBRARY})

add_dependencies(QtSql QtGui)

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtSql${CMAKE_DEBUG_POSTFIX}.so
        DESTINATION ${SITE_PACKAGE}/PySide)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtSql/pyside_qtsql_python.h
        DESTINATION include/PySide/QtSql/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_sql.xml
        DESTINATION share/PySide/typesystems)


