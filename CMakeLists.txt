cmake_minimum_required(VERSION 3.10)
project(MessengerProject)

set(CMAKE_CXX_STANDARD 17)

# Find FLTK
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIRS})

# Add subdirectories for client, server, and common libraries
add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)