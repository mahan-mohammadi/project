#include <iostream>
#include <map>
#include "userdb.h"
#include <functional>
#include "contact.h"
#include "contactsdb.h"

using namespace std;
using CommandHandler = function<void(int, stringstream&)>;

struct UserInfo {
    int id;
    bool isLogedIn = false;
};

class Server {
public:
    Server(int);
    void setPort(int);
    int getPort();
    void run();
    ~Server();
private:
    void setUpCommandMap();
    map<string, CommandHandler> commandMap;
    UserDB userdb;
    ContactsDB contactsdb;
    int port;
    int listener_fd;
    fd_set master_fds;
    int fd_max;
    map<int, UserInfo> clients;
    void handleRegister(int, stringstream&);
    void handleLogin(int, stringstream&);
    void handleSend(int, stringstream&);
    void handleHistory(int, stringstream&);
    void handleContacts(int, stringstream&);
};
