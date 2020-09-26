cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(MyCppLibsProject VERSION 1.0.1 DESCRIPTION 
"Reusable stuff for other c++ project")

set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../lib" CACHE FILEPATH "Library Output Path")

include_directories("..")

if(NOT DEFINED BOOST_PATH)
    message(WARNING "\nBOOST_PATH is not set....\nSome libraries won't be build")
    message(WARNING "\nYou can specify boost path with this run of cmake :\ncmake . -DBOOST_PATH=<absolute_boost_directory_path>")
endif(NOT DEFINED BOOST_PATH)

add_subdirectory("logger/")
add_subdirectory("network/")
add_subdirectory("OGL/")