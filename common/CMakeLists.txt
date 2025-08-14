
# Creates a static library named "common".
add_library(common STATIC
    user.cpp
    enc.cpp
    dec.cpp
)

# This makes the headers in this directory available to other targets that link against this library.
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
