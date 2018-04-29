cmake_minimum_required(VERSION 3.4)
project(PAMSI_2 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/)

add_executable(PAMSI_2
        src/main.cpp
        inc/insterfaces.hpp
        src/graph.cpp
        inc/graph.hpp
        src/station.cpp
        inc/station.hpp
        src/link_to_gnuplot.cpp
        inc/link_to_gnuplot.hpp
        src/Wektor2D.cpp
        inc/Wektor2D.hpp
        )

add_custom_target(run
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/"
    COMMAND PAMSI_2
)

add_custom_target(run_gui
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/../gui/"
    COMMAND python3 -m gui
)
