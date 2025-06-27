# Multithreaded C++ Chat Server

A terminal-based TCP chat server built in C++ using POSIX threads and Linux sockets.  
Supports multiple clients, real-time broadcasting, and modular architecture.

---

## 🧠 Features

- ✅ Handles **multiple clients concurrently** using POSIX threads
- ✅ Real-time **message broadcasting** to all connected clients
- ✅ Clean modular code with separate `include/` and `src/` folders
- ✅ Uses `Makefile` for easy build automation
- ✅ Designed to run inside a **Linux (WSL)** environment

---

## 🏗 Folder Structure

```
cpp-chat-server/
├── include/        # Header file with declarations
│   └── server.hpp
├── src/            # Main server logic
│   └── server.cpp
├── build/          # Compiled binary goes here
├── Makefile        # One-line build command
└── README.md
```

---

## ⚙️ Build & Run (in WSL/Linux)

### 1. Compile the Server
```bash
make
```

### 2. Run the Server
```bash
./build/chatserver
```

### 3. Simulate Clients
In separate terminals:
```bash
nc localhost 9002
```

---



## 📜 License

MIT License — free to use, modify, and share.
