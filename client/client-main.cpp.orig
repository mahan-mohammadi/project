#include "client.h"
#include <iostream>

int main() {

    string serverIP = "127.0.0.1";
    int port = 8080;
    Client client(serverIP, port);


    if (!client.connectToServer()) {
        cerr << "Failed to connect to the server." << endl;
        return 1;
    }
    
    cout << "Connected to the server." << endl;

    //temp
    string username = "testuser";
    string password = "TestPass";
    string loginCommand = "REGISTER " + username + " " + password;

    cout << "Attempting to log in as '" << username << "'..." << endl;
    

    client.sendMessage(loginCommand);

    string response = client.receiveMessage();

    if (response.rfind("SUCC", 0) == 0) {
        cout << "Login successful!" << endl;
    } else {
        cout << "Login failed. Server response: " << response << endl;
    }

    client.disconnectFromServer();
    cout << "Disconnected from the server." << endl;

    return 0;
}