

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
- [x] update README.mdadd the serialization logic to the client
- [x] and add tui to the apps
- [x] make a protocol so you can get your contacts from the server `CONTACTs`
- [x] add the contacts command logic
- [x] refactor contacts into its own class `contactsdb`
- [x] fix being able to send message to youreld
- [x] add the unused stuff (cmake) to git ignore
- [ ] fix the buff that messages have a space behind them


### 📊 Reporting System
- [ ] Add static counters in `Server` to track:
  - Number of users
  - Messages sent
  - Files transferred
- [x] Implement `GET_REPORT` command for clients to request stats and add dynamic memory allocation


---


## 🎨 Future Goals (Bonus)


- [x] Build a **Graphical User Interface (GUI)** for the client app check the fltk branch



