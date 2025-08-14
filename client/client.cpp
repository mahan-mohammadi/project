#include "client.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

/**
 * @brief Constructs the Client object.
 */
Client::Client(string serverIP, int port) {
    this->serverIP = serverIP;
    this->port = port;
    this->client_fd = -1;
    this->connected = false;
}

/**
 * @brief Destructor that ensures the connection is closed.
 */
Client::~Client() {
    if (connected) {
        disconnectFromServer();
    }
}

/**
 * @brief Connects to the server using the specified IP and port.
 * @return true on success, false on failure.
 */
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

/**
 * @brief Disconnects from the server.
 */
void Client::disconnectFromServer() {
    if (connected) {
        close(client_fd);
        connected = false;
        client_fd = -1;
    }
}

/**
 * @brief Sends a string message to the server.
 * @param message The message to send.
 * @return true on success, false on failure.
 */
bool Client::sendMessage(const string& message) {
    if (!connected) {
        return false;
    }

    // Send the message
    if (send(client_fd, message.c_str(), message.length(), 0) < 0) {
        // On error, assume disconnection
        disconnectFromServer();
        return false;
    }
    return true;
}

/**
 * @brief Waits to receive a message from the server. This is a blocking call.
 * @return The received message, or an empty string if an error occurs or the server disconnects.
 */
string Client::receiveMessage() {
    if (!connected) {
        return "";
    }

    char buffer[4096] = {0}; // Buffer for incoming data

    // Wait to receive data
    int bytesReceived = recv(client_fd, buffer, sizeof(buffer), 0);

    if (bytesReceived > 0) {
        // Successfully received data
        return string(buffer, bytesReceived);
    } else {
        // If recv returns 0 or -1, the connection is closed or an error occurred.
        disconnectFromServer();
        return "";
    }
}

/**
 * @brief Returns the connection status.
 * @return true if connected, false otherwise.
 */
bool Client::isConnected() const {
    return connected;
}
