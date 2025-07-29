#include "server.h"

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sstream>

Server::Server(int port) {
    this->port = port;

    // --- Create the socket ---
    this->listener_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->listener_fd == -1) {
        perror("socket"); // Print the system error message
        // In a real app, you would throw an exception here
        return;
    }

    // --- Specify the address ---
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(this->port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // --- Bind the socket ---
    if (bind(this->listener_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("bind");
        return;
    }

    // --- Listen on the socket ---
    if (listen(this->listener_fd, 5) == -1) {
        perror("listen");
        return;
    }

    std::cout << "Server setup complete. Listening on port " << this->port << std::endl;
    userdb.load();

    setUpCommandMap();
}

void Server::run() {
    // Clean and set up the master file descriptor set
    FD_ZERO(&this->master_fds);
    FD_SET(this->listener_fd, &this->master_fds);
    
    // Keep track of the highest file descriptor
    this->fd_max = this->listener_fd;

    std::cout << "Server is running. Waiting for connections..." << std::endl;

    while (true) {
        // select() is destructive, so we use a copy
        fd_set read_fds = this->master_fds;

        if (select(this->fd_max + 1, &read_fds, nullptr, nullptr, nullptr) == -1) {
            perror("select");
            return;
        }

        // Loop through all possible file descriptors
        for (int i = 0; i <= this->fd_max; i++) {
            if (FD_ISSET(i, &read_fds)) { // Check for activity on socket 'i'
                
                if (i == this->listener_fd) {
                    // --- Case 1: New connection on the listener socket ---
                    int new_client_fd = accept(this->listener_fd, nullptr, nullptr);
                    if (new_client_fd != -1) {
                        FD_SET(new_client_fd, &this->master_fds); // Add to master set
                        if (new_client_fd > this->fd_max) {
                            this->fd_max = new_client_fd; // Update max fd
                        }
                        std::cout << "New connection on socket " << new_client_fd << std::endl;
                    }
                } else {
                    // --- Case 2: Data from an existing client ---
                    char buffer[1024] = { 0 };
                    int bytes_received = recv(i, buffer, sizeof(buffer), 0);

                    if (bytes_received <= 0) {
                        // Client disconnected
                        std::cout << "Client on socket " << i << " disconnected." << std::endl;
                        close(i); // Close the socket
                        FD_CLR(i, &this->master_fds); // Remove from master set
                    } else {
                        // We got some data
                        std::cout << "Message from client " << i << ": " << buffer << std::endl;
                    }
                }
            }
        }
    }
}

void Server::setPort(int port){
  this->port = port;
}

int Server::getPort(){
  return this->port;
}

void Server::setUpCommandMap(){
    commandMap["REGISTER"] = [this](int client_fd , stringstream &ss){
        this->handleRegister(client_fd , ss);
    };
}

void Server::handleRegister(int client_fd , stringstream &ss){
    string username , encpassword , display;
    ss >> username >> display >> encpassword;
    if(userdb.userNameAlreadyExist(username)){
        send(client_fd, "ERROR Username is already taken.\n", 33, 0);
    }
    else{
        int id = userdb.getNewID();
        User newUser(id, username, display, encpassword);
        userdb.add(newUser);
        send(client_fd , "SUCC" , 5 , 0);
    }
}