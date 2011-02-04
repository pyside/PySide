project(pysidetest)
project(testbinding)

cmake_minimum_required(VERSION 2.6)

set(QT_USE_QTCORE 1)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
add_definitions(-DRXX_ALLOCATOR_INIT_0)

set(pysidetest_SRC
testobject.cpp
testview.cpp
)

set(pysidetest_MOC_HEADERS
testobject.h
testview.h
)

qt4_wrap_cpp(pysidetest_MOC_SRC ${pysidetest_MOC_HEADERS})

set(testbinding_SRC
${CMAKE_CURRENT_BINARY_DIR}/testbinding/testobject_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/testbinding/pysidecpp_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/testbinding/pysidecpp_testobjectwithnamespace_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/testbinding/pysidecpp2_testobjectwithoutnamespace_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/testbinding/testview_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/testbinding/testbinding_module_wrapper.cpp
)

add_custom_command(OUTPUT ${testbinding_SRC}
COMMAND ${GENERATORRUNNER_BINARY} ${GENERATOR_EXTRA_FLAGS}
        ${CMAKE_CURRENT_SOURCE_DIR}/pysidetest_global.h
        --include-paths=${pyside_BINARY_DIR}${PATH_SEP}${CMAKE_CURRENT_SOURCE_DIR}${PATH_SEP}${QT_INCLUDE_DIR}${PATH_SEP}${QT_QTCORE_INCLUDE_DIR}${PATH_SEP}${QT_QTGUI_INCLUDE_DIR}
        --typesystem-paths=${CMAKE_CURRENT_SOURCE_DIR}${PATH_SEP}${pyside_SOURCE_DIR}${PATH_SEP}${QtCore_SOURCE_DIR}${PATH_SEP}${QtGui_SOURCE_DIR}${PATH_SEP}${QtGui_BINARY_DIR}
        --output-directory=${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_pysidetest.xml
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
COMMENT "Running generator for test binding..."
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${QT_INCLUDE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTGUI_INCLUDE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${pyside_SOURCE_DIR}
                    ${QtCore_BINARY_DIR}/PySide/QtCore
                    ${QtGui_BINARY_DIR}/PySide/QtGui
                    ${libpyside_SOURCE_DIR}
                    ${SHIBOKEN_PYTHON_INCLUDE_DIR})

add_library(pysidetest SHARED ${pysidetest_SRC} ${pysidetest_MOC_SRC})
target_link_libraries(pysidetest ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

add_library(testbinding MODULE ${testbinding_SRC})
set_property(TARGET testbinding PROPERTY PREFIX "")
if(WIN32)
    set_target_properties(testbinding PROPERTIES SUFFIX ".pyd")
endif()
target_link_libraries(testbinding
                      pysidetest
                      pyside
                      ${PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      ${SBK_PYTHON_LIBRARIES})

add_dependencies(testbinding pyside QtCore QtGui libpyside pysidetest)


PYSIDE_TEST(decoratedslot_test.py)
PYSIDE_TEST(delegatecreateseditor_test.py)
PYSIDE_TEST(homonymoussignalandmethod_test.py)
PYSIDE_TEST(list_signal_test.py)
PYSIDE_TEST(modelview_test.py)
PYSIDE_TEST(signalandnamespace_test.py)
PYSIDE_TEST(signalwithdefaultvalue_test.py)
PYSIDE_TEST(signalemissionfrompython_test.py)
PYSIDE_TEST(version_test.py)

