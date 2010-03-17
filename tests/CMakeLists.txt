
file(GLOB TEST_FILES */*_test.py)

set(test_blacklist )

foreach(test_file ${TEST_FILES})
    string(REGEX MATCH "/([^/]+)//?([^/]+)_test.py" test_name ${test_file} )
    list(FIND test_blacklist ${CMAKE_MATCH_1}_${CMAKE_MATCH_2} expect_fail)
    add_test(${CMAKE_MATCH_1}_${CMAKE_MATCH_2} sh
             ${CMAKE_CURRENT_SOURCE_DIR}/run_test.sh
             "${pysidebase_BINARY_DIR}"
             "${CMAKE_BINARY_DIR}:${CMAKE_CURRENT_SOURCE_DIR}/util"
             ${PYTHON_EXECUTABLE}
             ${test_file})
    set_tests_properties(${CMAKE_MATCH_1}_${CMAKE_MATCH_2} PROPERTIES TIMEOUT 5)
    if (${expect_fail} GREATER -1)
        set_tests_properties(${CMAKE_MATCH_1}_${CMAKE_MATCH_2} PROPERTIES WILL_FAIL TRUE)
    endif(${expect_fail} GREATER -1)
# Should set python path here
# Looks like it's fixed in 2.8:
# http://www.vtk.org/Bug/print_bug_page.php?bug_id=7885
endforeach(test_file ${TEST_FILES})
