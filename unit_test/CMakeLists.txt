### minimum version of cmake
set(CMAKE_VERSION 2.8.12.2)
cmake_minimum_required(VERSION ${CMAKE_VERSION})
message("-- Minimum required version of CMake is ${CMAKE_VERSION}")


### name of the project
set(PROJECT_NAME test_smartDescriptor)
project(${PROJECT_NAME})
message("-- Project name is ${PROJECT_NAME}")


### Appends the cmake path to MAKE_MODULE_PATH variable.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
message("-- CMake module path is ${CMAKE_MODULE_PATH}")

### file(GLOB...) allows for wildcard additions:

##file(GLOB SOURCES "../libs/ngrams/*.cpp" "test_src/test_NgramExtractor.cpp" "test_src/module.cpp" )
#file(GLOB SOURCES "../libs/*.cpp" "test_src/module.cpp" "test_src/test_File.cpp" "test_src/test_FileBinary.cpp"
#                  "test_src/test_FileParameters.cpp" "test_src/test_NgramExtractor.cpp" "../libs/ngrams/*.cpp" "../libs/readerFile/*.cpp"  )

file(GLOB SOURCES "test_src/module.cpp" "../libs/readerCsv/*.cpp" "../libs/readerFile/*.cpp" "../libs/buffer/*.cpp"
                   "../libs/detection/*.cpp" "../libs/header/*.cpp" "test_src/test_DetectEmail.cpp")

### name of the binary
set(TARGET_NAME test_smartDescriptor)
add_executable(${TARGET_NAME} ${SOURCES})

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -fexceptions")

### Bring the headers
target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/smartDescriptor/header/
        ${PROJECT_SOURCE_DIR}/../libs/readerFile/
        ${PROJECT_SOURCE_DIR}/../libs/readerCsv/
        ${PROJECT_SOURCE_DIR}/../libs/util/
        ${PROJECT_SOURCE_DIR}/../libs/ngrams/
        ${PROJECT_SOURCE_DIR}/../libs/buffer/
        ${PROJECT_SOURCE_DIR}/../libs/header/
        ${PROJECT_SOURCE_DIR}/../libs/detection/
        ${PROJECT_SOURCE_DIR}/test_src/
        ${PROJECT_SOURCE_DIR}/../smartDescriptor/
        PUBCLIC ${PYTHON_INCLUDE_DIRS})

### link libs
set(ALL_LIBARIES boost_system boost_filesystem boost_unit_test_framework archive boost_iostreams z bz2 archive)

target_link_libraries(${TARGET_NAME} ${ALL_LIBARIES})
install(TARGETS ${TARGET_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
