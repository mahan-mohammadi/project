#include "clientApp.h"
#include <iostream>

App::App(): client(IP, PORT){
 //empty
}

void App::drawMainMenu(){
    system("clear");
    std::cout << "  ┌──────────────────────────────────────────┐\n";
    std::cout << "  │                                          │\n";
    std::cout << "  │       Welcome to Your Messanger CLI      │\n";
    std::cout << "  │                                          │\n";
    std::cout << "  ├──────────────────────────────────────────┤\n";
    std::cout << "  │                                          │\n";
    std::cout << "  │           ┌────────────────────┐         │\n";
    std::cout << "  │           │      1.Login       │         │\n";
    std::cout << "  │           └────────────────────┘         │\n";
    std::cout << "  │           ┌────────────────────┐         │\n";
    std::cout << "  │           │      2.Register    │         │\n";
    std::cout << "  │           └────────────────────┘         │\n";
    std::cout << "  │                                          │\n";
    std::cout << "  │                                          │\n";
    std::cout << "  └──────────────────────────────────────────┘\n";
}

void App::run(){
    if (!client.connectToServer()) {
        std::cerr << "Failed to connect to the server." << std::endl;
        return;
    }
    drawMainMenu();
    bool running = false;
    while (running) {

        int choice;
        cout << "Enter your choice (1, 2, or 3 for exit): ";
        cin >> choice;
        switch (choice) {
            case 1:
                loginMenu();
                break;
            case 2:
                registerMenu();
                break;
            case 3:
                running = false;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
}
    client.disconnectFromServer();
    std::cout << "Disconnected from the server." << std::endl;
}