# 🧩 Project Phases & TODOs

## ✅ Phase 1: Core User Management (🔨 Current Focus)

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
- [ ] Integrate `Encryptor` into `UserManager` to encrypt passwords before saving
- [ ] Add them to the user class

### 🌐 Integrate into Server
- [ ] Add a `UserManager` member to the `Server` class
- [ ] Implement `REGISTER` command in `Server::run()` using `userManager.registerUser()`

---

## 🖥️ Phase 2: Client Application & Login

### 🧑‍💻 Client Class
- [ ] Implement `client.h` and `client.cpp`
- [ ] Write logic to connect to the server
- [ ] Use a **two-threaded model**:
  - Thread 1: Send user input
  - Thread 2: Receive server messages

### 🔑 LOGIN Command
- [ ] Add login logic to `UserManager` (verify username and password)
- [ ] Add `LOGIN` command to server using `UserManager`
- [ ] Use `std::map<int, UserInfo> clients` in `Server` to track logged-in users

---

## 💬 Phase 3: Private Messaging & File Storage

### 📩 SEND Command
- [ ] Client sends: `SEND <recipient_username> <message>`
- [ ] Server parses the command
- [ ] Server saves message to `<recipient_username>.txt`

### 📥 CHECK_MESSAGES Command
- [ ] Client sends `CHECK_MESSAGES`
- [ ] Server reads `<username>.txt`
- [ ] Server sends file contents back to the client

---

## 📁 Phase 4: File Transfer & Reporting

### 📤 File Transfer
- [ ] Define protocol: `SENDFILE <recipient> <filename>`
- [ ] Client sends file in chunks to server
- [ ] Server forwards file in chunks to recipient client

### 📊 Reporting System
- [ ] Add static counters in `Server` to track:
  - Number of users
  - Messages sent
  - Files transferred
- [ ] Implement `GET_REPORT` command for clients to request stats

---

## 🎨 Future Goals (Bonus)

- [ ] Build a **Graphical User Interface (GUI)** for the client app (Qt/GTK/ncurses/etc.)

---

## ✅ Tips
- Use `// TODO:` comments in code to reference these checkboxes.
- Consider using `clang-tidy` or `cppcheck` to keep code clean.
