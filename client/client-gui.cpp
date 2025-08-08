#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Group.H>
#include "client.h"
#include <string>
#include <iostream>
#include <cstring> // For strlen

// GUI Widgets
Fl_Double_Window *win;
Fl_Group *grp_main_menu, *grp_connect, *grp_chat, *grp_log;
Fl_Input *in_ip, *in_port, *in_user, *in_pass, *in_recipient, *in_message;
Fl_Button *btn_connect, *btn_login, *btn_register, *btn_send, *btn_history, *btn_set_recipient;
Fl_Button *btn_show_connect, *btn_show_chat, *btn_show_log;
Fl_Text_Display *disp_log, *disp_chat;
Fl_Text_Buffer *buff_log, *buff_chat;

Client *client = nullptr;
std::string current_recipient = "";

void show_group(Fl_Group* grp) {
    grp_main_menu->hide();
    grp_connect->hide();
    grp_chat->hide();
    grp_log->hide();
    grp->show();
}

void show_main_menu_cb(Fl_Widget*) {
    show_group(grp_main_menu);
}

void log_message(const std::string& msg) {
    buff_log->append(msg.c_str());
    buff_log->append("\n");
}

void chat_message(const std::string& msg) {
    buff_chat->append(msg.c_str());
    buff_chat->append("\n");
}

void connect_cb(Fl_Widget*) {
    const char* ip = in_ip->value();
    const char* port_str = in_port->value();
    if (strlen(ip) == 0 || strlen(port_str) == 0) {
        log_message("IP and Port are required.");
        show_group(grp_log);
        return;
    }
    int port = std::stoi(port_str);

    if (client) {
        client->disconnectFromServer();
        delete client;
        client = nullptr;
    }
    client = new Client(ip, port);

    if (client->connectToServer()) {
        log_message("Connected to server.");
        btn_connect->label("Disconnect");
        show_group(grp_chat);
    } else {
        log_message("Failed to connect.");
        delete client;
        client = nullptr;
        show_group(grp_log);
    }
}

void login_cb(Fl_Widget*) {
    if (!client || !client->isConnected()) {
        log_message("Not connected to server.");
        show_group(grp_log);
        return;
    }
    std::string user = in_user->value();
    std::string pass = in_pass->value();
    if (user.empty() || pass.empty()) {
        log_message("Username and password are required.");
        show_group(grp_log);
        return;
    }
    std::string login_command = "LOGIN " + user + " " + pass;
    client->sendMessage(login_command);
    std::string response = client->receiveMessage();
    log_message("Server response: " + response);
    show_group(grp_log);
}

void register_cb(Fl_Widget*) {
    if (!client || !client->isConnected()) {
        log_message("Not connected to server.");
        show_group(grp_log);
        return;
    }
    std::string user = in_user->value();
    std::string pass = in_pass->value();
    if (user.empty() || pass.empty()) {
        log_message("Username and password are required.");
        show_group(grp_log);
        return;
    }
    std::string register_command = "REGISTER " + user + " " + user + " " + pass;
    client->sendMessage(register_command);
    std::string response = client->receiveMessage();
    log_message("Server response: " + response);
    show_group(grp_log);
}

void set_recipient_cb(Fl_Widget*) {
    current_recipient = in_recipient->value();
    if (!current_recipient.empty()) {
        log_message("Chatting with: " + current_recipient);
        chat_message(("--- Chat with " + current_recipient + " ---").c_str());
    } else {
        log_message("Recipient cleared.");
    }
    show_group(grp_log);
}


void send_cb(Fl_Widget*) {
    if (!client || !client->isConnected()) {
        log_message("Not connected to server.");
        show_group(grp_log);
        return;
    }
    if (current_recipient.empty()) {
        log_message("Please set a recipient first.");
        show_group(grp_log);
        return;
    }
    std::string message = in_message->value();
    if (message.empty()) {
        log_message("Message is required.");
        show_group(grp_log);
        return;
    }
    std::string send_command = "SEND " + current_recipient + " " + message;
    client->sendMessage(send_command);
    std::string response = client->receiveMessage();
    log_message("Server response: " + response);
    in_message->value(""); // Clear message input after sending
}

void history_cb(Fl_Widget*) {
    if (!client || !client->isConnected()) {
        log_message("Not connected to server.");
        show_group(grp_log);
        return;
    }
     if (current_recipient.empty()) {
        log_message("Please set a recipient first.");
        show_group(grp_log);
        return;
    }
    std::string history_command = "HISTORY " + current_recipient;
    client->sendMessage(history_command);
    std::string response = client->receiveMessage();

    buff_chat->text("");
    chat_message("--- History with " + current_recipient + " ---");
    chat_message(response);
    chat_message("--- End of History ---");
    show_group(grp_chat);
}


int main(int argc, char **argv) {
    win = new Fl_Double_Window(800, 600, "Mahan's FLTK Chat Client");

    // Main Menu
    grp_main_menu = new Fl_Group(10, 10, 780, 580, "Main Menu");
    {
        btn_show_connect = new Fl_Button(300, 200, 200, 50, "Connect / Login");
        btn_show_connect->callback([](Fl_Widget*){ show_group(grp_connect); });
        btn_show_chat = new Fl_Button(300, 260, 200, 50, "Chat");
        btn_show_chat->callback([](Fl_Widget*){ show_group(grp_chat); });
        btn_show_log = new Fl_Button(300, 320, 200, 50, "View Log");
        btn_show_log->callback([](Fl_Widget*){ show_group(grp_log); });
    }
    grp_main_menu->end();

    // Connection and Login View
    grp_connect = new Fl_Group(10, 10, 780, 580, "Connection");
    {
        in_ip = new Fl_Input(120, 55, 200, 25, "Server IP:");
        in_ip->value("127.0.0.1");
        in_port = new Fl_Input(120, 85, 100, 25, "Port:");
        in_port->value("8080");
        btn_connect = new Fl_Button(120, 115, 120, 25, "Connect");
        btn_connect->callback(connect_cb);

        in_user = new Fl_Input(120, 165, 200, 25, "Username:");
        in_pass = new Fl_Input(120, 195, 200, 25, "Password:");
        in_pass->type(FL_SECRET_INPUT);
        btn_login = new Fl_Button(120, 225, 100, 25, "Login");
        btn_login->callback(login_cb);
        btn_register = new Fl_Button(230, 225, 100, 25, "Register");
        btn_register->callback(register_cb);
        
        Fl_Button *back_btn1 = new Fl_Button(10, 560, 100, 25, "Back");
        back_btn1->callback(show_main_menu_cb);
    }
    grp_connect->end();
    grp_connect->hide();

    // Chat View
    grp_chat = new Fl_Group(10, 10, 780, 580, "Chat");
    {
        in_recipient = new Fl_Input(80, 25, 140, 25, "To:");
        btn_set_recipient = new Fl_Button(230, 25, 100, 25, "Set Recipient");
        btn_set_recipient->callback(set_recipient_cb);
        
        in_message = new Fl_Input(80, 55, 520, 25, "Message:");
        btn_send = new Fl_Button(610, 55, 70, 25, "Send");
        btn_send->callback(send_cb);
        btn_history = new Fl_Button(690, 55, 70, 25, "History");
        btn_history->callback(history_cb);
        
        disp_chat = new Fl_Text_Display(20, 90, 760, 460);
        buff_chat = new Fl_Text_Buffer();
        disp_chat->buffer(buff_chat);
        
        Fl_Button *back_btn2 = new Fl_Button(10, 560, 100, 25, "Back");
        back_btn2->callback(show_main_menu_cb);
    }
    grp_chat->end();
    grp_chat->hide();
    
    // Log View
    grp_log = new Fl_Group(10, 10, 780, 580, "Log");
    {
         disp_log = new Fl_Text_Display(20, 25, 760, 525);
         buff_log = new Fl_Text_Buffer();
         disp_log->buffer(buff_log);
         
         Fl_Button *back_btn3 = new Fl_Button(10, 560, 100, 25, "Back");
         back_btn3->callback(show_main_menu_cb);
    }
    grp_log->end();
    grp_log->hide();
    

    win->resizable(win);
    win->end();
    win->show(argc, argv);
    
    show_group(grp_main_menu);

    return Fl::run();
}