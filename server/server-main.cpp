#include "server.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Default port number
    int port = 8080;

    // Optional: Allow setting the port from the command line
    if (argc > 1) {
        try {
            port = std::stoi(argv[1]);
        } catch (const std::exception& e) {
            cout << "Invalid port number provided. Using default " << port << "." << endl;
        }
    }

    try {
        // Create the server object with the specified port
        Server server(port);

        // Start the server's main loop. This will block and run forever.
        server.run();

    } catch (const std::exception& e) {
        cout << "An unexpected error occurred" << endl;
        return 1; // Indicate error
    }

    return 0; // This line will likely never be reached
}
