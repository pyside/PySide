include(icecc.cmake) # this must be the first line!

project(pysidebindings)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -DNDEBUG -Os -Wl,-O1 -Wl,--hash-style=gnu -Wno-strict-aliasing -fvisibility=hidden")
set(CMAKE_CXX_FLAGS_DEBUG "-g -fno-common -Wall -fno-strict-aliasing -fvisibility=hidden")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

option(AVOID_PROTECTED_HACK "Avoid protected hack on generated bindings." FALSE)
if (AVOID_PROTECTED_HACK OR WIN32)
    add_definitions(-DAVOID_PROTECTED_HACK)
    message(STATUS "Avoiding protected hack!")
endif()

find_package(PythonLibs REQUIRED)
find_package(PythonInterp REQUIRED)
find_package(Shiboken REQUIRED)
find_package(Qt4 4.5.0 REQUIRED)

set(BINDING_NAME PySide)
set(BINDING_API_MAJOR_VERSION "0")
set(BINDING_API_MINOR_VERSION "3")
set(BINDING_API_MICRO_VERSION "0")
set(BINDING_API_VERSION "${BINDING_API_MAJOR_VERSION}.${BINDING_API_MINOR_VERSION}.${BINDING_API_MICRO_VERSION}")

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE PATH "The subdirectory relative to the install prefix where libraries will be installed (default is /lib${LIB_SUFFIX})" FORCE)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

include(${QT_USE_FILE})
if (${QTVERSION} VERSION_LESS 4.5.0)
    message(FATAL_ERROR "You need Qt4.5, found ${QTVERSION}.")
endif()

set(BINDING_VERSION ${BINDING_API_VERSION}.${QT_VERSION_MAJOR}.${QT_VERSION_MINOR})
find_program(GENERATOR generatorrunner REQUIRED)

if (NOT GENERATOR)
    message(FATAL_ERROR "You need to specify GENERATOR variable (-DGENERATOR=value)")
endif()

# uninstall target
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake"
               "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
               IMMEDIATE @ONLY)
add_custom_target(uninstall "${CMAKE_COMMAND}"
                  -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")


set(ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-qt${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}+${BINDING_API_VERSION})
add_custom_target(dist
    COMMAND mkdir -p "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}" &&
            git log > "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}/ChangeLog" &&
            git archive --prefix=${ARCHIVE_NAME}/ HEAD --format=tar -o "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar" &&
            tar -C "${CMAKE_BINARY_DIR}" --owner=root --group=root -r "${ARCHIVE_NAME}/ChangeLog" -f "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar" &&
            bzip2 -f9 "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar" &&
            echo "Source package created at ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.bz2.\n"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

execute_process(
    COMMAND ${PYTHON_EXECUTABLE} -c "from distutils import sysconfig; \\
        print sysconfig.get_python_lib(1,0,prefix='${CMAKE_INSTALL_PREFIX}')"
    OUTPUT_VARIABLE SITE_PACKAGE
    OUTPUT_STRIP_TRAILING_WHITESPACE)
if (NOT SITE_PACKAGE)
    message(FATAL_ERROR "Could not detect Python module installation directory.")
endif()

set(GENERATOR_EXTRA_FLAGS --generatorSet=shiboken --enable-parent-ctor-heuristic --enable-pyside-extensions --enable-return-value-heuristic)

enable_testing()

add_subdirectory(libpyside)
# project directories
add_subdirectory(${BINDING_NAME})
add_subdirectory(tests)
