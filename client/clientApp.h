#include "client.h"

#define IP "127.0.0.1"
#define PORT 8080

using namespace std;

class App{
    public:
    App();
    void run();
    private:
    Client client;
    void drawPrimaryMenu();
    void loginMenu();
    void registerMenu();
    void mainAppMenu();
    void drawMainMenu();
    string username;
};