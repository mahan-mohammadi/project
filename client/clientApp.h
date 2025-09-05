#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include "client.h"
#include "json.hpp"
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Browser.H>
#include <vector>
#include <FL/Fl_Hold_Browser.H>
#define IP "127.0.0.1"
#define PORT 8080


using json = nlohmann::json;

class App {
public:
    App();
    void run();

private:
    Client client;
    std::string username;
    json contacts_list;
    
    string welcome_message_text;    
    Fl_Window *win;
    Fl_Button *login_button, *register_button, *send_button, *contacts_button, *stats_button, *exit_button;
    Fl_Input *username_input, *password_input, *display_name_input, *recipient_input, *message_input;
    Fl_Browser *contacts_browser;
    Fl_Text_Display *messages_display;
    Fl_Text_Buffer *messages_buffer;
    Fl_Box *status_box;

    void show_primary_menu();
    void show_login_menu();
    void show_register_menu();
    void show_main_app_menu();
    void show_send_message_menu();
    void show_messages_with_contact(const std::string& contact_username);
    void show_stats();


    static void login_cb(Fl_Widget*, void*);
    static void register_cb(Fl_Widget*, void*);
    static void send_message_cb(Fl_Widget*, void*);
    static void view_contacts_cb(Fl_Widget*, void*);
    static void contact_selected_cb(Fl_Widget*, void*);
    void contact_selected();
    static void view_stats_cb(Fl_Widget*, void*);
    static void back_to_main_cb(Fl_Widget*, void*);


    void login();
    void register_user();
    void send_message();
    void view_contacts();
    void get_stats();
};

#endif // CLIENTAPP_H
