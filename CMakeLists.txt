### minimum version of cmake
set(CMAKE_VERSION 2.8.12.2)
cmake_minimum_required(VERSION ${CMAKE_VERSION})
message("-- Minimum required version of CMake is ${CMAKE_VERSION}")


### name of the project
set(PROJECT_NAME smartDescriptor)
project(${PROJECT_NAME})
message("-- Project name is ${PROJECT_NAME}")

#unit test
add_subdirectory(unit_test)

### Appends the cmake path to MAKE_MODULE_PATH variable.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
message("-- CMake module path is ${CMAKE_MODULE_PATH}")

file(GLOB SOURCES "libs/readerFile/*.cpp" "libs/ngrams/*.cpp" "libs/util/*.cpp"
        "libs/header/*.cpp" "libs/*.cpp"
        "libs/readerCsv/*.cpp" "libs/encoding/*.cpp"
        "libs/buffer/*.cpp" "libs/detection/*.cpp" "libs/*.cpp")

### name of the binary
set(TARGET_NAME smartDescriptor)
add_executable(${TARGET_NAME} ${SOURCES})


### shared libraries need PIC
set_property(TARGET ${TARGET_NAME} PROPERTY POSITION_INDEPENDENT_CODE 1)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -DSQLITE_THREADSAFE=1 -fexceptions")

### Bring the headers
target_include_directories(${TARGET_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/libs/header/
        ${PROJECT_SOURCE_DIR}/libs/readerFile/
        ${PROJECT_SOURCE_DIR}/libs/readerCsv/
        ${PROJECT_SOURCE_DIR}/libs/encoding/
        ${PROJECT_SOURCE_DIR}/libs/analysis/
        ${PROJECT_SOURCE_DIR}/libs/ngrams/
        ${PROJECT_SOURCE_DIR}/libs/util/
        ${PROJECT_SOURCE_DIR}/libs/buffer/
        ${PROJECT_SOURCE_DIR}/smartDescriptor/
        PUBLIC ${PYTHON_INCLUDE_DIRS})

set(ALL_LIBARIES boost_filesystem boost_system boost_regex
        boost_unit_test_framework archive boost_iostreams archive z bz2)


target_link_libraries(${TARGET_NAME} ${ALL_LIBARIES})
install(TARGETS ${TARGET_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
