#include "clientApp.h"
#include <iostream>
#include "userutils.h"
#include "enc.h"

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
    cout << "Disconnected from the server." << std::endl;
}

void App::registerMenu(){
    system("clear");
    string username, displayName, password;
    cout << "-------- Register --------\n";

    do {
        cout << "Enter username (4-15 chars): ";
        cin >> username;
    } while (!UserUtils::isUsernameValid(username));

    cout << "Enter display name: ";
    cin >> displayName;

    do {
        cout << "Enter password (8-20 chars,letters and numbers only): ";
        cin >> password;
    } while (!UserUtils::isPassValid(password));

    Encryption enc(password);
    string command = "REGISTER " + username + " " + displayName + " " + enc.getEncText();

    client.sendMessage(command);
    string response = client.receiveMessage();
    // checks if "SUCC" is found starting at position 0.
    if (response.find("SUCC", 0) == 0){
        cout << "Registration successful! You can now log in." << endl;
    } else {
        cout << "Registration failed. Server response: " << response << endl;
    }

    cout << "Press enter to continue...";
    int garbage;
    cin >>garbage;

}

void App::loginMenu(){
    system("clear");
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    Encryption enc(password);
    string command = "LOGIN " + username + " " + enc.getEncText();

    client.sendMessage(command);
    string response = client.receiveMessage();

    if (response.find("SUCC", 0) == 0){
        cout << "\nLogin successful!" << endl;
        // Here you would transition to the main part of your application
        // For now, we'll just show a message.
        cout << "Welcome back, " << username << "!" << endl;
    } else {
        cout << "\nLogin failed. Server response: " << response << endl;
    }

    cout << "Press enter to continue...";
    int garbage;
    cin >>garbage;
}