
# Creates an executable named "client".
add_executable(client
    client-main.cpp
    client.cpp
    clientApp.cpp
    userutils.cpp
)

# Links the client executable against the "common" library.
target_link_libraries(client PRIVATE common)
