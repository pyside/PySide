include(icecc.cmake) # this must be the first line!

project(pysidebindings)

cmake_minimum_required(VERSION 2.6)

if(CMAKE_HOST_UNIX)
    option(ENABLE_GCC_OPTIMIZATION "Enable specific GCC flags to optimization library size and performance. Only available on Release Mode" 0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fvisibility=hidden -Wno-strict-aliasing")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    if(ENABLE_GCC_OPTIMIZATION)
        set(CMAKE_BUILD_TYPE Release)
        set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -Os -Wl,-O1")
        if(NOT CMAKE_HOST_APPLE)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--hash-style=gnu")
        endif()
    endif()

    if(CMAKE_HOST_APPLE)
        if (NOT QT_INCLUDE_DIR)
            set(QT_INCLUDE_DIR "/Library/Frameworks")
         endif()
    endif()
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

option(AVOID_PROTECTED_HACK "Avoid protected hack on generated bindings." FALSE)
if(AVOID_PROTECTED_HACK OR WIN32)
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
set(BINDING_API_MICRO_VERSION "3")
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

# Configure OS support
if(Q_WS_X11)
    set(ENABLE_X11 "1")
    set(ENABLE_MAC "0")
    set(ENABLE_WIN "0")
    if(Q_WS_MAEMO_5)
        set(AUTO_OS "MAEMO 5")
    else()
        set(AUTO_OS "X11")
    endif()
elseif(Q_WS_MAC)
    set(ENABLE_X11 "0")
    set(ENABLE_MAC "1")
    set(ENABLE_WIN "0")
    set(AUTO_OS "MAC")
elseif(Q_WS_WIN)
    set(ENABLE_X11 "0")
    set(ENABLE_MAC "0")
    set(ENABLE_WIN "1")
    set(AUTO_OS "WIN")
else()
    message(FATAL_ERROR "OS not supported")
endif()
message(STATUS "Detected OS: ${AUTO_OS}")

# Define supported Qt Version
if(${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} GREATER 6)
    set(SUPPORTED_QT_VERSION 4.7)
else()
    set(SUPPORTED_QT_VERSION 4.6)
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


set(ARCHIVE_NAME pyside-qt${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}+${BINDING_API_VERSION})
add_custom_target(dist
    COMMAND mkdir -p "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}" &&
            git log > "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}/ChangeLog" &&
            git archive --prefix=${ARCHIVE_NAME}/ HEAD --format=tar --output="${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar" &&
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

set(GENERATOR_EXTRA_FLAGS "--generatorSet=shiboken --enable-parent-ctor-heuristic --enable-pyside-extensions --enable-return-value-heuristic")

enable_testing()

add_subdirectory(libpyside)
# project directories
add_subdirectory(${BINDING_NAME})
add_subdirectory(tests)
add_subdirectory(doc)
