
# Creates an executable named "server".
add_executable(server
    server-main.cpp
    server.cpp
    userdb.cpp
    message.cpp
    messagedb.cpp
    contact.cpp
    statsdb.cpp
    contactsdb.cpp
)

# Links the server executable against the "common" library.
target_link_libraries(server PRIVATE common)
