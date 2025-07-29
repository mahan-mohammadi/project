#include <iostream>
#include <map>
#include "userdb.h"
#include <functional>

using namespace std;
using CommandHandler = function<void(int , stringstream&)>;

struct UserInfo{
  int id;
  bool isLogedIn = false;
};

class Server{
  public:
    Server(int);
    void setPort(int);
    int getPort();
    void run();
    ~Server();
  private:
    void setUpCommandMap();
    map<string , CommandHandler> commandMap;
    UserDB userdb;
    int port;
    int listener_fd;
    fd_set master_fds;
    int fd_max;
    map<int , UserInfo> clients;
    void handleRegister(int , stringstream&);
};
