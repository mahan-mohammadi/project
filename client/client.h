#ifndef CLIENT_H
#define CLIENT_H

#include <string>

using namespace std;

class Client {
public:
    Client(string serverIP, int port);
    ~Client();
    bool connectToServer();
    void disconnectFromServer();

    //Returns false on error.
    bool sendMessage(string message);
    string receiveMessage();
    bool isConnected();
private:
    string serverIP;
    int port;
    int client_fd;
    bool connected;
};

#endif
