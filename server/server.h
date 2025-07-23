#include <iostream>
#include <map>

using namespace std;

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
    int port;
    int listener_fd;
    fd_set master_fds;
    int fd_max;
    map<int , UserInfo> clients;
   
};
