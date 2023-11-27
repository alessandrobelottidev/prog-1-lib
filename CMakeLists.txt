cmake_minimum_required(VERSION 3.26)
project(magic LANGUAGES CXX)

include_directories(external/catch2)

set(CMAKE_CXX_STANDARD 11)

set(LIBRARY_FILES
        include/magic/magic.hpp
#        lib/magic.ipp
)
add_library(magic SHARED ${LIBRARY_FILES})
set_target_properties(magic PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(magic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_include_directories(magic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/magic)


set(TEST_FILES
        tests/test_main.cpp
)
add_executable(tests ${TEST_FILES})
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external)
target_link_libraries(tests PRIVATE magic)


set(EXAMPLE_FILES
        examples/es1_2023_11_23.cpp
        examples/es3_2023_11_23.cpp
        examples/es4_2023_11_23.cpp
)

# Create example executables
foreach(EXAMPLE_FILE ${EXAMPLE_FILES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_FILE})
    # Link examples with the library
    target_link_libraries(${EXAMPLE_NAME} magic)
endforeach()

# TODO: move all tests to multiple files
add_executable(temp tests/tests.cpp)
target_link_libraries(temp magic)