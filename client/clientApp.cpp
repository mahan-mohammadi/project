#include "clientApp.h"
#include <iostream>
#include "userutils.h"
#include "enc.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

App::App(): client(IP, PORT){
 //empty
}

void App::drawPrimaryMenu(){
    system("clear");
    cout << "  ┌──────────────────────────────────────────┐\n";
    cout << "  │                                          │\n";
    cout << "  │       Welcome to Your Messanger CLI      │\n";
    cout << "  │                                          │\n";
    cout << "  ├──────────────────────────────────────────┤\n";
    cout << "  │                                          │\n";
    cout << "  │           ┌────────────────────┐         │\n";
    cout << "  │           │      1.Login       │         │\n";
    cout << "  │           └────────────────────┘         │\n";
    cout << "  │           ┌────────────────────┐         │\n";
    cout << "  │           │      2.Register    │         │\n";
    cout << "  │           └────────────────────┘         │\n";
    cout << "  │                                          │\n";
    cout << "  │                                          │\n";
    cout << "  └──────────────────────────────────────────┘\n";
}


void App::primaryMenu(){
    bool running = false;
    while (!running) {
        drawPrimaryMenu();
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
}

void App::run(){
    if (!client.connectToServer()) {
        cerr << "Failed to connect to the server." << endl;
        return;
    }

    primaryMenu();
    
    client.disconnectFromServer();
    cout << "Disconnected from the server." << endl;
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
        this->username = username;
        mainAppMenu();
    } else {
        cout << "\nLogin failed. Server response: " << response << endl;
    }

    cout << "Press 0 to continue...";
    int garbage;
    cin >>garbage;
}

void App::mainAppMenu(){
    system("clear");

    bool valid = false;
    while(!valid){
        int choice;
        drawMainMenu();
        cout << "Enter your choice (1, 2, 3 , 4 ): ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            viewContactsMenu();
            break;
        case 2:
            sendMessageMenu();
            break;
        case 3:
            //getStats();
            break;
        case 4:
            primaryMenu();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}

void App::drawMainMenu(){
    system("clear");
    cout << "   logged in as " << this->username << '\n';
    cout << "  ┌──────────────────────────────────────────┐\n";
    cout << "  │                                          │\n";
    cout << "  ├──────────────────────────────────────────┤\n";
    cout << "  │                                          │\n";
    cout << "  │      1. View All Contacts                │\n";
    cout << "  │      2. Send Message                     │\n";
    cout << "  │      3. Get Stats                        │\n";
    cout << "  │      4. Exit                             │\n";
    cout << "  │                                          │\n";
    cout << "  └──────────────────────────────────────────┘\n";
}

void App::sendMessageMenu() {
    system("clear");
    string recipient, message;

    cout << "Enter recipient's username: ";
    cin >> recipient;

    cout << "Enter your message: ";
    cin.ignore(); //clean the \n
    getline(cin, message);

    string command = "SEND " + recipient + " " + message;

    client.sendMessage(command);
    string response = client.receiveMessage();

    if (response.find("SUCC", 0) == 0) {
        cout << "\nMessage sent successfully!" << endl;
    } else {
        cout << "\nFailed to send message. Server response: " << response << endl;
    }

    cout << "Press enter to continue...";
    cin.get(); 
}


void App::viewContactsMenu(){
    system("clear");
    cout << "┌──────────────────────────┐\n";
    cout << "│      Your Contacts       │\n";
    cout << "└──────────────────────────┘\n\n";

    string command = "CONTACTS";
    client.sendMessage(command);
    string response = client.receiveMessage();
    
      if (response.rfind("ERROR", 0) == 0) {
        cout << "Could not retrieve contacts. Server response: " << response << endl;
    } else if (response.empty()) {
        cout << "You don't have any contacts yet. Send a message to add one!\n";
    } else {
            json contactslist = json::parse(response);

            if (contactslist.empty()) {
                cout << "You don't have any contacts yet. Send a message to add one!\n";
            } else {
                int count = 1;
                cout << "------------------------------------------\n";
                for (json contact : contactslist) {
                    string displayName = contact.at("displayName").get<string>();
                    string username = contact.at("username").get<string>();
                    cout << "  " << count << ". " << displayName << " (@" << username << ")\n";
                    count++;
                }
                cout << "------------------------------------------\n";
                cout << "Enter a contact number to view messages, or 0 to go back: ";
                int choice;
                cin >> choice;

                if ( choice < 0 || choice > count) {
                     cout << "\nInvalid choice. Returning to the main menu." << endl;
            }
                else{
                    int index = 1;
                    for (json contact : contactslist){
                        if(index == choice){
                            string contactUsername = contact.at("username").get<string>();

                            viewMessagesWithContact(contactUsername);
                            return;
                        }
                        index++;
                    }
                }
        }

    cout << "Press enter to continue...";
    cin.ignore(); //the enter from the previous menu still causes problem here
    cin.get(); 
}
}

void App::viewMessagesWithContact(string contactUsername){
    system("clear");
    cout << "┌──────────────────────────────────────────┐\n";
    cout << "│        Messages with contact             │ \n";
    cout << "└──────────────────────────────────────────┘\n\n";

    string command = "HISTORY" + contactUsername;
    client.sendMessage(command);
    string response = client.receiveMessage();

    if (response.rfind("ERROR", 0) == 0) {
        cout << "Could not retrieve messages. Server response: " << response << endl;
    } else {
        json messages = json::parse(response);
        if (messages.empty()) {
                cout << "No messages with this user yet. Be the first to say hi!" << endl;
        } else {
            for(json message : messages){
                string content = message.at("message").get<string>();
            }
        }
    } 
     cout << "Press enter to continue...";
    cin.get();
}