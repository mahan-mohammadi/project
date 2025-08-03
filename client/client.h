#ifndef CLIENT_H
#define CLIENT_H

#include <string>

using namespace std;

class Client {
public:
    Client(const string& serverIP, int port);
    ~Client();

    // Establishes the connection to the server.
    bool connectToServer();

    // Closes the connection.
    void disconnectFromServer();

    // Sends a message to the server. Returns false on error.
    bool sendMessage(const string& message);

    // Waits for and returns a message from the server.
    // Returns an empty string on error or disconnection.
    string receiveMessage();

    // Checks if the client is currently connected.
    bool isConnected() const;

private:
    string serverIP;
    int port;
    int client_fd;
    bool connected;
};

#endif // CLIENT_H
