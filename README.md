Secure Client-Server Chat Application

This project is a secure, multi-client chat application built in C++ using the Linux Sockets API.
📋 Project To-Do List
Phase 1: Core User Management (Current Focus)

    [ ] Create User Class:

        [x] Define the data structure for a single user (user.h).

        [ ] Implement the methods in user.cpp.

        [ ] (New) Reformat constructors to use member initializer lists for better C++ practice.

    [ ] Create UserManager Class:

        [ ] Implement UserManager.h with method declarations (registerUser, userExists).

        [ ] Implement UserManager.cpp with file I/O logic to read/write to users.txt.

    [ ] Implement Custom Encryption:

        [ ] (New) Create a simple Encryptor class (Encryptor.h, Encryptor.cpp).

        [ ] (New) Add methods for encryption and decryption (e.g., using a XOR cipher).

        [ ] Integrate the Encryptor into the UserManager to process passwords before they are saved.

    [ ] Integrate UserManager into Server:

        [ ] Add a UserManager member to the Server class.

        [ ] Implement a REGISTER command in the Server::run() method to call userManager.registerUser().

Phase 2: Client Application & Login

    [ ] Create Client Class:

        [ ] Implement client.h and client.cpp.

        [ ] Write logic to connect to the server.

        [ ] Create a two-threaded model: one for sending user input, one for receiving server messages.

    [ ] Implement LOGIN Command:

        [ ] Add login logic to UserManager to verify a username and password from the file.

        [ ] Add a LOGIN command to the server that uses the UserManager.

        [ ] Use the std::map<int, UserInfo> clients map in the server to track the logged-in state of each client.

Phase 3: Private Messaging & File Storage

    [ ] Implement SEND Command:

        [ ] The client will send messages in the format: SEND <recipient_username> <message>.

        [ ] The server will parse this command.

        [ ] The server will save the message to a file named <recipient_username>.txt.

    [ ] Implement CHECK_MESSAGES Command:

        [ ] The client will send a CHECK_MESSAGES command.

        [ ] The server will read the contents of the user's message file (<username>.txt).

        [ ] The server will send the contents of the file back to the client.

Phase 4: File Transfer & Reporting

    [ ] Implement File Transfer:

        [ ] Define a protocol for initiating a file transfer (e.g., SENDFILE <recipient> <filename>).

        [ ] Implement logic for sending the file in chunks from client to server.

        [ ] Implement logic for forwarding the file in chunks from server to the destination client.

    [ ] Implement Reporting System:

        [ ] Add static counters to the Server class for tracking users, messages, and files.

        [ ] Implement a GET_REPORT command that clients can use to request the statistics.

Future Goals (Bonus)

    [ ] Implement a Graphical User Interface (GUI) for the client application.
