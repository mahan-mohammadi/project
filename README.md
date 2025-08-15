# 🧩 Project Phases & TODOs

## ✅ Phase 1: Core User Management

### 👤 User Class
- [x] Define the data structure for a single user (`user.h`)
- [x] Implement the methods in `user.cpp`
- [x] ♻️ Reformat constructors to use **member initializer lists** for better C++ practices

### 📋 UserManager Class
- [x] make a way so that you can get a new id for new users
- [x] Implement `UserManager.h` with method declarations (`registerUser`, `userExists`)
- [x] Implement `UserManager.cpp` with file I/O logic to read/write `users.txt`

### 🔐 Custom Encryption
- [x] Create `Encryptor` class (`Encryptor.h`, `Encryptor.cpp`)
- [x] Add encryption/decryption methods (e.g., simple XOR cipher)
- ~~[ ] Integrate `Encryptor` into `UserManager` to encrypt passwords before saving~~
- ~~[ ] Add them to the user class~~

### 🌐 Integrate into Server
- [x] Add a `UserManager` member to the `Server` class
- [x] Implement `REGISTER` command in `Server::run()` using `userManager.registerUser()`

---

## 🖥️ Phase 2: Client Application & Login

### 🧑‍💻 Client Class
- [x] Implement `client.h` and `client.cpp`
- [x] Write logic to connect to the server
- [ ] ~~Use a **two-threaded model**:~~
  - ~~Thread 1: Send user input~~
  - ~~Thread 2: Receive server messages~~

### 🔑 LOGIN Command
- [x] Add login logic to `UserManager` (verify username and password)
- [x] Add `LOGIN` command to server using `UserManager`
- [x] Use `std::map<int, UserInfo> clients` in `Server` to track logged-in users

---

## 💬 Phase 3: Private Messaging & File Storage
### 📩 SEND Command
- [x] implement message logic
- [x] Client sends: `SEND <recipient_username> <message>`
- [x] Server parses the command
- [x] Server saves message to `<id>-<id>.txt`

### 📥 CHECK_MESSAGES Command
- [x] Client sends `HISTORY`
- [x] Server reads `<id>-<id>.txt`
- [x] Server sends file contents back to the client

---

## 📁 Phase 4: client & Reporting (🔨 Current Focus)

### 🎨 the client
- [x] add the serialization logic to the client
- [x] and add tui to the apps
- [x] make a protocol so you can get your contacts from the server `CONTACTs`
- [x] add the contacts command logic
- [x] refactor contacts into its own class `contactsdb`
- [x] fix being able to send message to youreld
- [ ] add the unused stuff (cmake) to git ignore

### 📊 Reporting System
- [ ] Add static counters in `Server` to track:
  - Number of users
  - Messages sent
  - Files transferred
- [ ] Implement `GET_REPORT` command for clients to request stats

---

## 🎨 Future Goals (Bonus)

- [ ] Build a **Graphical User Interface (GUI)** for the client app (Qt/GTK/ncurses/etc.)

