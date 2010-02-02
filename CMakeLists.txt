include(icecc.cmake) # this must be the first line!

project(pysidebindings)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -DNDEBUG -Os -Wl,-O1 -Wl,--hash-style=gnu -Wno-strict-aliasing -fvisibility=hidden")
set(CMAKE_CXX_FLAGS_DEBUG "-g -fno-common -Wall -fno-strict-aliasing -fvisibility=hidden")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_BUILD_TYPE)

find_package(PythonLibs REQUIRED)
find_package(PythonInterp REQUIRED)
find_package(Shiboken REQUIRED)
find_package(Qt4 4.5.0 REQUIRED)

set(BINDING_NAME PySide)
set(BINDING_API_MAJOR_VERSION "0")
set(BINDING_API_MINOR_VERSION "1")
set(BINDING_API_VERSION "${BINDING_API_MAJOR_VERSION}.${BINDING_API_MINOR_VERSION}")

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE PATH "The subdirectory relative to the install prefix where libraries will be installed (default is /lib${LIB_SUFFIX})" FORCE)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_BUILD_TYPE)

include(${QT_USE_FILE})
if (${QTVERSION} VERSION_LESS 4.5.0)
    message(FATAL_ERROR "You need Qt4.5, found ${QTVERSION}.")
endif (${QTVERSION} VERSION_LESS 4.5.0)

set(BINDING_VERSION ${BINDING_API_VERSION}.${QT_VERSION_MAJOR}.${QT_VERSION_MINOR})
find_program(GENERATOR generatorrunner REQUIRED)

if (NOT GENERATOR)
    message(FATAL_ERROR "You need to specify GENERATOR variable (-DGENERATOR=value)")
endif (NOT GENERATOR)

# uninstall target
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake"
               "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
               IMMEDIATE @ONLY)
add_custom_target(uninstall "${CMAKE_COMMAND}"
                  -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")


set(ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-${BINDING_API_VERSION})
add_custom_target(dist
    COMMAND git archive --prefix=${ARCHIVE_NAME}/ HEAD
        | bzip2 > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.bz2
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

execute_process(
    COMMAND ${PYTHON_EXECUTABLE} -c "from distutils import sysconfig; \\
        print sysconfig.get_python_lib(1,0,prefix='${CMAKE_INSTALL_PREFIX}')"
    OUTPUT_VARIABLE SITE_PACKAGE
    OUTPUT_STRIP_TRAILING_WHITESPACE)
if (NOT SITE_PACKAGE)
    message(FATAL_ERROR "Could not detect Python module installation directory.")
endif (NOT SITE_PACKAGE)

set(GENERATOR_EXTRA_FLAGS --generatorSet=shiboken --enable-parent-ctor-heuristic --enable-pyside-extensions --enable-return-value-heuristic)

enable_testing()

add_subdirectory(libpyside)
# project directories
add_subdirectory(${BINDING_NAME})
add_subdirectory(tests)
