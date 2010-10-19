project(pysidetest)
project(testbinding)

cmake_minimum_required(VERSION 2.6)
find_package(Qt4 4.5.0 REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(PythonInterpWithDebug REQUIRED)
find_package(GeneratorRunner 0.6 REQUIRED)
find_package(Shiboken 0.5 REQUIRED)


set(QT_USE_QTCORE 1)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
add_definitions(-DRXX_ALLOCATOR_INIT_0)

set(pysidetest_SRC
testobject.cpp
)

set(pysidetest_MOC_HEADERS
testobject.h
)

qt4_wrap_cpp(pysidetest_MOC_SRC ${pysidetest_MOC_HEADERS})

set(testbinding_SRC
${CMAKE_CURRENT_BINARY_DIR}/testbinding/testobject_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/testbinding/testbinding_module_wrapper.cpp
)

set(GENERATOR_EXTRA_FLAGS --generatorSet=shiboken --enable-parent-ctor-heuristic --enable-pyside-extensions --enable-return-value-heuristic)
add_custom_command(OUTPUT ${testbinding_SRC}
COMMAND ${GENERATORRUNNER_BINARY} ${GENERATOR_EXTRA_FLAGS}
        ${CMAKE_CURRENT_SOURCE_DIR}/global.h
        --include-paths=${CMAKE_CURRENT_SOURCE_DIR}:${QT_INCLUDE_DIR}:${QT_QTCORE_INCLUDE_DIR}
        --typesystem-paths=${CMAKE_CURRENT_SOURCE_DIR}:${pyside_SOURCE_DIR}:${QtCore_SOURCE_DIR}
        --output-directory=${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_pysidetest.xml
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
COMMENT "Running generator for test binding..."
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${QT_INCLUDE_DIR}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${QtCore_BINARY_DIR}/PySide/QtCore
                    ${libpyside_SOURCE_DIR}
                    ${PYTHON_INCLUDE_PATH})

add_library(pysidetest SHARED ${pysidetest_SRC} ${pysidetest_MOC_SRC})
target_link_libraries(pysidetest ${QT_QTCORE_LIBRARY})

add_library(testbinding MODULE ${testbinding_SRC})
set_property(TARGET testbinding PROPERTY PREFIX "")
target_link_libraries(testbinding
                      pysidetest
                      pyside
                      ${PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
                      ${QT_QTCORE_LIBRARY}
                      ${SBK_PYTHON_LIBRARIES})

add_dependencies(testbinding pyside QtCore libpyside pysidetest)


PYSIDE_TEST(homonymoussignalandmethod_test.py)

