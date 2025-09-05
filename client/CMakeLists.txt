# Sources for the client
set(CLIENT_SOURCES
    client-main.cpp
    client.cpp
    clientApp.cpp
    userutils.cpp
)

# Add the executable for the client
add_executable(client ${CLIENT_SOURCES})

# Link libraries
target_link_libraries(client common ${FLTK_LIBRARIES})