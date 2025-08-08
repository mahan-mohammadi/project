#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include "client.h"
#include <string>
#include <iostream>

// GUI Widgets
Fl_Double_Window *win;
Fl_Input *in_ip, *in_port, *in_user, *in_pass, *in_recipient, *in_message;
Fl_Button *btn_connect, *btn_login, *btn_register, *btn_send, *btn_history;
Fl_Text_Display *disp_log, *disp_chat;
Fl_Text_Buffer *buff_log, *buff_chat;

Client *client = nullptr;

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
        return;
    }
    int port = std::stoi(port_str);

    if (client) {
        client->disconnectFromServer();
        delete client;
    }
    client = new Client(ip, port);

    if (client->connectToServer()) {
        log_message("Connected to server.");
        btn_connect->label("Disconnect");
    } else {
        log_message("Failed to connect.");
        delete client;
        client = nullptr;
    }
}

void login_cb(Fl_Widget*) {
    if (!client || !client->isConnected()) {
        log_message("Not connected to server.");
        return;
    }
    std::string user = in_user->value();
    std::string pass = in_pass->value();
    if (user.empty() || pass.empty()) {
        log_message("Username and password are required.");
        return;
    }
    std::string login_command = "LOGIN " + user + " " + pass;
    client->sendMessage(login_command);
    std::string response = client->receiveMessage();
    log_message("Server response: " + response);
}

void register_cb(Fl_Widget*) {
    if (!client || !client->isConnected()) {
        log_message("Not connected to server.");
        return;
    }
    std::string user = in_user->value();
    std::string pass = in_pass->value();
    if (user.empty() || pass.empty()) {
        log_message("Username and password are required.");
        return;
    }
    std::string register_command = "REGISTER " + user + " " + user + " " + pass;
    client->sendMessage(register_command);
    std::string response = client->receiveMessage();
    log_message("Server response: " + response);
}

void send_cb(Fl_Widget*) {
    if (!client || !client->isConnected()) {
        log_message("Not connected to server.");
        return;
    }
    std::string recipient = in_recipient->value();
    std::string message = in_message->value();
    if (recipient.empty() || message.empty()) {
        log_message("Recipient and message are required.");
        return;
    }
    std::string send_command = "SEND " + recipient + " " + message;
    client->sendMessage(send_command);
    std::string response = client->receiveMessage();
    log_message("Server response: " + response);
}

void history_cb(Fl_Widget*) {
    if (!client || !client->isConnected()) {
        log_message("Not connected to server.");
        return;
    }
    std::string recipient = in_recipient->value();
    if (recipient.empty()) {
        log_message("Recipient is required.");
        return;
    }
    std::string history_command = "HISTORY " + recipient;
    client->sendMessage(history_command);
    std::string response = client->receiveMessage();
    chat_message("History with " + recipient + ":\n" + response);
}


int main(int argc, char **argv) {
  win = new Fl_Double_Window(800, 600, "FLTK Client");

  in_ip = new Fl_Input(80, 25, 140, 25, "Server IP:");
  in_ip->value("127.0.0.1");
  in_port = new Fl_Input(280, 25, 70, 25, "Port:");
  in_port->value("8080");
  btn_connect = new Fl_Button(360, 25, 100, 25, "Connect");
  btn_connect->callback(connect_cb);

  in_user = new Fl_Input(80, 75, 140, 25, "Username:");
  in_pass = new Fl_Input(280, 75, 140, 25, "Password:");
  btn_login = new Fl_Button(430, 75, 70, 25, "Login");
  btn_login->callback(login_cb);
  btn_register = new Fl_Button(510, 75, 70, 25, "Register");
  btn_register->callback(register_cb);


  disp_log = new Fl_Text_Display(20, 120, 760, 100, "Log");
  buff_log = new Fl_Text_Buffer();
  disp_log->buffer(buff_log);

  in_recipient = new Fl_Input(80, 240, 140, 25, "To:");
  in_message = new Fl_Input(280, 240, 200, 25, "Message:");
  btn_send = new Fl_Button(490, 240, 70, 25, "Send");
  btn_send->callback(send_cb);
  btn_history = new Fl_Button(570, 240, 70, 25, "History");
  btn_history->callback(history_cb);


  disp_chat = new Fl_Text_Display(20, 280, 760, 300, "Chat");
  buff_chat = new Fl_Text_Buffer();
  disp_chat->buffer(buff_chat);


  win->end();
  win->show(argc, argv);
  return Fl::run();
}