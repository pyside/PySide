INCLUDE(FindPythonInterp)

find_package(PythonInterp REQUIRED)

#Fix missing variable on UNIX env
if(NOT PYTHON_DEBUG_LIBRARIES AND UNIX)
    set(PYTHON_DEBUG_LIBRARIES "${PYTHON_LIBRARIES}")
endif()

if(PYTHONINTERP_FOUND AND UNIX AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    # This is for Debian
    set(PYTHON_EXECUTABLE_TMP "${PYTHON_EXECUTABLE}-dbg")

    # Fall back to the standard interpreter.
    if(NOT EXISTS "${PYTHON_EXECUTABLE_TMP}")
        set(PYTHON_EXECUTABLE_TMP "${PYTHON_EXECUTABLE}")
    endif()

    set(PYTHON_EXECUTABLE "${PYTHON_EXECUTABLE_TMP}")
endif()

