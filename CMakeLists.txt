
# Sets the minimum required version of CMake.
cmake_minimum_required(VERSION 3.10)

# Sets the project name.
project(MessagingApp)

# Sets the C++ standard to C++17. This is based on your VS Code settings.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the common directory to the include path for all targets.
include_directories(common)

# Add the subdirectories that contain their own CMakeLists.txt files.
add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)
