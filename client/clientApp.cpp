#include "clientApp.h"
#include "userutils.h"
#include "enc.h"
#include "json.hpp"
#include <iostream>
#include <ctime>
#include <sstream>


using json = nlohmann::json;

App::App() : client(IP, PORT) {
    win = nullptr;
}

void App::run() {
    if (!client.connectToServer()) {

        cout << "Failed to connect to the server." << endl;

        return;
    }
    show_primary_menu();
    Fl::run();
    client.disconnectFromServer();
    std::cout << "Disconnected from the server." << std::endl;
}

void App::show_primary_menu() {
    if (win) delete win;
    win = new Fl_Window(400, 300, "Messenger CLI");
    win->resizable(win);

    new Fl_Box(100, 40, 200, 40, "Welcome to Your Messenger");

    login_button = new Fl_Button(150, 100, 100, 30, "Login");
    login_button->callback([](Fl_Widget* w, void* data){
        ((App*)data)->show_login_menu();
    }, this);

    register_button = new Fl_Button(150, 150, 100, 30, "Register");
    register_button->callback([](Fl_Widget* w, void* data){
        ((App*)data)->show_register_menu();
    }, this);

    win->end();
    win->show();
}

void App::show_login_menu() {
    if (win) delete win;
    win = new Fl_Window(400, 300, "Login");
    win->resizable(win);

    username_input = new Fl_Input(150, 50, 200, 30, "Username:");
    password_input = new Fl_Input(150, 100, 200, 30, "Password:");
    password_input->type(FL_SECRET_INPUT);

    login_button = new Fl_Button(150, 150, 100, 30, "Login");
    login_button->callback(login_cb, this);

    status_box = new Fl_Box(50, 200, 300, 25, "");


    win->end();
    win->show();
}

void App::login_cb(Fl_Widget*, void* data) {
    ((App*)data)->login();
}

void App::login() {
    std::string user = username_input->value();
    std::string pass = password_input->value();

    Encryption enc(pass);
    std::string command = "LOGIN " + user + " " + enc.getEncText();

    client.sendMessage(command);
    std::string response = client.receiveMessage();

    if (response.find("SUCC", 0) == 0) {
        this->username = user;
        show_main_app_menu();
    } else {
        status_box->label("Login failed. Check your credentials.");
        win->redraw();
    }
}

void App::show_register_menu() {
    if (win) delete win;
    win = new Fl_Window(400, 400, "Register");
    win->resizable(win);

    username_input = new Fl_Input(150, 50, 200, 30, "Username:");
    display_name_input = new Fl_Input(150, 100, 200, 30, "Display Name:");
    password_input = new Fl_Input(150, 150, 200, 30, "Password:");
    password_input->type(FL_SECRET_INPUT);

    register_button = new Fl_Button(150, 200, 100, 30, "Register");
    register_button->callback(register_cb, this);

    status_box = new Fl_Box(50, 250, 300, 25, "");

    win->end();
    win->show();
}

void App::register_cb(Fl_Widget*, void* data) {
    ((App*)data)->register_user();
}

void App::register_user() {
    std::string user = username_input->value();
    std::string display_name = display_name_input->value();
    std::string pass = password_input->value();

    if (!UserUtils::isUsernameValid(user)) {
        status_box->label("Invalid username (4-15 chars).");
        win->redraw();
        return;
    }
    if (!UserUtils::isPassValid(pass)) {
        status_box->label("Invalid password (8-20 chars, letters & numbers).");
        win->redraw();
        return;
    }

    Encryption enc(pass);
    std::string command = "REGISTER " + user + " " + display_name + " " + enc.getEncText();

    client.sendMessage(command);
    std::string response = client.receiveMessage();

    if (response.find("SUCC", 0) == 0) {
        show_login_menu();
    } else {
        status_box->label("Registration failed. Try a different username.");
        win->redraw();
    }
}

void App::show_main_app_menu() {
    if (win) delete win;
    win = new Fl_Window(400, 400, "Main Menu");
    win->resizable(win);

    welcome_message_text = "Logged in as " + this->username;
    new Fl_Box(100, 20, 200, 20, welcome_message_text.c_str());

    contacts_button = new Fl_Button(100, 80, 200, 40, "View Contacts");
    contacts_button->callback(view_contacts_cb, this);

    send_button = new Fl_Button(100, 140, 200, 40, "Send Message");
    send_button->callback(send_message_cb, this);

    stats_button = new Fl_Button(100, 200, 200, 40, "Get Stats");
    stats_button->callback(view_stats_cb, this);

    exit_button = new Fl_Button(150, 260, 100, 30, "Logout");
    exit_button->callback([](Fl_Widget* w, void* data){
        ((App*)data)->show_primary_menu();
    }, this);

    win->end();
    win->show();
}

void App::view_contacts_cb(Fl_Widget*, void* data) {
    ((App*)data)->view_contacts();
}

void App::view_contacts() {
    if(win) delete win;
    win = new Fl_Window(500, 400, "Contacts");
    win->resizable(win);


    contacts_browser = new Fl_Hold_Browser(20, 20, 460, 300, "Your Contacts");
    contacts_browser->callback(contact_selected_cb, this);
    contacts_browser->when(FL_WHEN_CHANGED);
    Fl_Button* back_button = new Fl_Button(200, 340, 100, 30, "Back");
    back_button->callback(back_to_main_cb, this);

    std::string command = "CONTACTS";
    client.sendMessage(command);
    std::string response = client.receiveMessage();

    if (response.find("ERROR", 0) == 0) {
        cout << "Could not retrieve contacts. Server response: " << response << endl;
    } else if (response.empty() || response == "[]") {
        contacts_browser->add("You don't have any contacts yet.");
    } else {
        contacts_list = json::parse(response);
        for (const auto& contact : contacts_list) {
            std::string item = contact["displayName"].get<std::string>() + " (@" + contact["username"].get<std::string>() + ")";
            contacts_browser->add(item.c_str());
        }
    }

    win->end();
    win->show();
}

void App::contact_selected_cb(Fl_Widget*, void* data) {
    ((App*)data)->contact_selected();
}

void App::contact_selected() {
    int index = contacts_browser->value();
    if (index > 0 && index <= (int)contacts_list.size()) {
        std::string contact_username = contacts_list[index - 1]["username"].get<std::string>();
        show_messages_with_contact(contact_username);
    }
}

void App::show_messages_with_contact(const std::string& contact_username) {
    if (win) delete win;
    win = new Fl_Window(500, 500, ("Messages with " + contact_username).c_str());
    win->resizable(win);

    messages_display = new Fl_Text_Display(20, 20, 460, 400);
    messages_buffer = new Fl_Text_Buffer();
    messages_display->buffer(messages_buffer);

    Fl_Button* back_button = new Fl_Button(200, 440, 100, 30, "Back");
    back_button->callback(back_to_main_cb, this);

    std::string command = "HISTORY " + contact_username;
    client.sendMessage(command);
    std::string response = client.receiveMessage();

    if (response.find("ERROR", 0) == 0) {
        messages_buffer->text("Could not retrieve messages.");
    } else {
        json messages = json::parse(response);
        if (messages.empty()) {
            messages_buffer->text("No messages with this user yet.");
        } else {
            std::stringstream ss;
            for (const auto& message : messages) {
                ss << "From: " << message["senderDisplayName"].get<std::string>() << "\n";
                ss << message["message"].get<std::string>() << "\n";
                time_t timestamp = message.at("timestamp").get<time_t>();
                ss << "Time: " << UserUtils::formatTimestamp(timestamp) << "\n";
                ss << "-----------------------------------\n";
            }
            messages_buffer->text(ss.str().c_str());
        }
    }

    win->end();
    win->show();
}


void App::send_message_cb(Fl_Widget*, void* data) {
    ((App*)data)->show_send_message_menu();
}


void App::show_send_message_menu() {
    if (win) delete win;
    win = new Fl_Window(400, 300, "Send Message");
    win->resizable(win);


    recipient_input = new Fl_Input(150, 50, 200, 30, "Recipient:");
    message_input = new Fl_Input(150, 100, 200, 100, "Message:");

    send_button = new Fl_Button(150, 220, 100, 30, "Send");
    send_button->callback([](Fl_Widget* w, void* data){
        ((App*)data)->send_message();
    }, this);

    Fl_Button* back_button = new Fl_Button(260, 220, 100, 30, "Back");
    back_button->callback(back_to_main_cb, this);

    status_box = new Fl_Box(50, 260, 300, 25, "");


    win->end();
    win->show();
}

void App::send_message() {
    std::string recipient = recipient_input->value();
    std::string message = message_input->value();

    std::string command = "SEND " + recipient + " " + message;
    client.sendMessage(command);
    std::string response = client.receiveMessage();


    if (response.find("SUCC", 0) == 0) {
        status_box->label("Message sent successfully!");

    } else {
        status_box->label("Failed to send message.");
    }
    win->redraw();
}

void App::view_stats_cb(Fl_Widget*, void* data) {
    ((App*)data)->get_stats();
}

void App::get_stats() {
    if(win) delete win;
    win = new Fl_Window(400, 200, "Your Stats");
    win->resizable(win);

    Fl_Text_Buffer* stats_buffer = new Fl_Text_Buffer();
    Fl_Text_Display* stats_display = new Fl_Text_Display(20, 20, 360, 100, "Stats");
    stats_display->buffer(stats_buffer);

    Fl_Button* back_button = new Fl_Button(150, 140, 100, 30, "Back");
    back_button->callback(back_to_main_cb, this);

    std::string command = "STATS";
    client.sendMessage(command);
    std::string response = client.receiveMessage();

    if (response.find("ERROR", 0) == 0) {
        stats_buffer->text("Could not retrieve stats.");
    } else {
        std::stringstream ss(response);
        int messageNum, contactNum;
        ss >> messageNum >> contactNum;

        std::string stats_text = "Contacts: " + std::to_string(contactNum) + "\nMessages: " + std::to_string(messageNum);
        stats_buffer->text(stats_text.c_str());
    }

    win->end();
    win->show();
}

void App::back_to_main_cb(Fl_Widget*, void* data) {
    ((App*)data)->show_main_app_menu();
}
