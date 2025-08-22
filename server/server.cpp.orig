#include "server.h"
#include "messagedb.h"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sstream>
#include <fstream>

Server::Server(int port) {
    this->port = port;

    // --- Create the socket ---
    this->listener_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->listener_fd == -1) {
        perror("socket"); 
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

Server::~Server() {

    if (listener_fd != -1) {
        close(listener_fd);
    }
    std::cout << "Server shut down." << std::endl;
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
                        // the buffer is 1kb so it has a lot of garbage daa
                        stringstream ss(string(buffer, bytes_received));
                        string command;
                        ss >> command;
                        auto f = commandMap.find(command);
                        if(f != commandMap.end()) {
                            //first is the key second is the value
                            f->second(i,ss);
                        }
                        else {
                            send(i, "ERROR Unknown command\n", 22, 0);
                        }
                    }
                }
            }
        }
    }
}

void Server::setPort(int port) {
    this->port = port;
}

int Server::getPort() {
    return this->port;
}

void Server::setUpCommandMap() {
    commandMap["REGISTER"] = [this](int client_fd, stringstream &ss) {
        this->handleRegister(client_fd, ss);
    };
    commandMap["LOGIN"] = [this](int client_fd, stringstream &ss) {
        this->handleLogin(client_fd,ss);
    };
    commandMap["SEND"] = [this](int client_fd , stringstream &ss){
        this->handleSend(client_fd,ss);
    };
    commandMap["HISTORY"] = [this](int client_fd , stringstream &ss){
        this->handleHistory(client_fd , ss);
    };
    commandMap["CONTACTS"] = [this](int client_fd, stringstream &ss){
        this->handleContacts(client_fd, ss);
    };
}

void Server::handleRegister(int client_fd, stringstream &ss) {
    string username, encpassword, display;
    ss >> username >> display >> encpassword;
    if(userdb.userNameAlreadyExist(username)) {
        cout << "username : " << username << " was already taken";
        send(client_fd, "ERROR Username is already taken.\n", 33, 0);
    }
    else {
        cout << "handling the registeration for username: " << username << endl;
        int id = userdb.getNewID();
        User newUser(id, username, display, encpassword);
        userdb.add(newUser);
        send(client_fd, "SUCC", 5, 0);
    }
}

void Server::handleLogin(int client_fd, stringstream& ss) {
    string username, encpass;
    ss >> username >> encpass;
    User* user = userdb.findUserByUsername(username);
    if(user != nullptr) {
        if(user->getPass() == encpass) {
            cout << "loging in the user: " << username << endl;
            clients[client_fd].isLogedIn = true;
            clients[client_fd].id = user->getID();
            send(client_fd, "SUCC\n", 5, 0);
        } else {
            cout << "user: " << username << " password was wrong!" << endl;
            send(client_fd, "ERROR Invalid credentials\n", 26, 0);
        }
    } else {
        cout << "user: " << username << " doesnt exist in the db" << endl;
        send(client_fd, "ERROR User not found\n", 21, 0);
    }
}

void Server::handleSend(int client_fd, stringstream& ss) {
    if (!clients[client_fd].isLogedIn) {
        send(client_fd, "ERROR Not logged in\n", 20, 0);
        return;
    }

    string recipientUsername, message;
    ss >> recipientUsername;
    getline(ss, message);

    User* recipient = userdb.findUserByUsername(recipientUsername);
    if (recipient == nullptr) {
        cout << "reciver user doesnt exsit" << endl;
        send(client_fd, "ERROR User not found\n", 21, 0);
        return;
    }

    int senderId = clients[client_fd].id;
    User* sender = userdb.findUserById(senderId);

    if (sender == nullptr) {
        send(client_fd, "ERROR Could not identify sender.\n", 32, 0);
        return;
    }

    if (senderId == recipient->getID()) {
        send(client_fd, "ERROR You can't send a message to yourself.\n", 43, 0);
        return;
    }

    // Add each user to the other's contact list
    contactsdb.addContact(senderId, *recipient);
    contactsdb.addContact(recipient->getID(), *sender);

    string senderDisplayName = sender->getDName();
    string reciverDisplayName = recipient->getDName();

    MessageDB::saveMessage(Message(senderId, recipient->getID(), message , senderDisplayName , reciverDisplayName ));

    cout << "a message was sent between " << senderId << " and " << recipient->getID() << endl;
    send(client_fd, "SUCC\n", 5, 0);
}

void Server::handleHistory(int client_fd, stringstream& ss) {
    if (!clients[client_fd].isLogedIn) {
        cout << "user is not logged in" << endl;
        send(client_fd, "ERROR Not logged in\n", 20, 0);
        return;
    }

    string contact;
    ss >> contact;

    User* reciver = userdb.findUserByUsername(contact);
    if (reciver == nullptr) {
        cout << "user was not found" << endl;
        send(client_fd, "ERROR User not found\n", 21, 0);
        return;
    }

    json history = MessageDB::getMessagesOf(clients[client_fd].id, reciver->getID());
    string historyStr = history.dump();

    cout << "sending history to " <<  clients[client_fd].id << endl;
    send(client_fd, historyStr.c_str(), historyStr.length(), 0);
}

void Server::handleContacts(int client_fd , stringstream& ss){
    if (!clients[client_fd].isLogedIn) {
        send(client_fd, "ERROR Not logged in\n", 20, 0);
        return;
    }

    int userId = clients[client_fd].id;
    ifstream contactsFile("contacts.json");
    
    json allContacts;
    contactsFile >> allContacts;

    string userIdStr = to_string(userId); //all json keys are strings so it cant be int

    
    //end points to the position just after the array in json
    if (allContacts.find(userIdStr) != allContacts.end()) {
        json userContacts = allContacts[userIdStr];
        string responseStr = userContacts.dump();

        //return a c style string not std::string
        send(client_fd, responseStr.c_str(), responseStr.length(), 0);
    } else {
        send(client_fd, "[]", 2, 0);
    }
}