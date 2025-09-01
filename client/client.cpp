#include "client.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

Client::Client(string serverIP, int port) {
    this->serverIP = serverIP;
    this->port = port;
    this->client_fd = -1;
    this->connected = false;
}

/**
 make sure the fd is closed so it detects the user change
 */
Client::~Client() {
    if (connected) {
        disconnectFromServer();
    }
}

bool Client::connectToServer() {
    // Create socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        return false;
    }

    // Specify server address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, serverIP.c_str(), &serverAddress.sin_addr) <= 0) {
        return false;
    }

    // Connect
    if (connect(client_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        return false;
    }

    connected = true;
    return true;
}

void Client::disconnectFromServer() {
    if (connected) {
        close(client_fd);
        connected = false;
        client_fd = -1;
    }
}


bool Client::sendMessage(string message) {
    if (!connected) {
        return false;
    }

    if (send(client_fd, message.c_str(), message.length(), 0) < 0) {

        disconnectFromServer();
        return false;
    }
    return true;
}


string Client::receiveMessage() {
    if (!connected) {
        return "";
    }

    char buffer[4096] = {0}; // 4kb of Buffer for incoming data had to use c string


    int bytesReceived = recv(client_fd, buffer, sizeof(buffer), 0);


    /*Data received: The number is positive.

    Connection closed: The number is zero.

    An error occurred: The number is negative.*/
    
    if (bytesReceived > 0) {
        // Successfully received data
        return string(buffer, bytesReceived);
    } else {
        disconnectFromServer();
        return "";
    }
}

bool Client::isConnected() {
    return connected;
}
