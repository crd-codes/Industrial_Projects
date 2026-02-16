# Concurrent TCP File Transfer Server

---

## 📌 Project Overview

This project is a Client–Server File Transfer Application developed in C using TCP sockets.
The server listens for client requests and sends the requested file, while the client connects to the server, requests a file, and downloads it locally.

The system supports multiple clients simultaneously using process-based concurrency using `fork()`.

---

## 🏗️ Technologies Used

- C Programming
- Linux System Calls
- Socket Programming (TCP)
- Process Management (`fork()`)
- File Handling (open, read, write, stat)

---

## ✨ Features

- TCP-based reliable file transfer
- Multi-client support using `fork()`
- Sends file size before transfer (header-based protocol)
- Transfers file in chunks (1024 bytes)
- Error handling if file is not found
- Command-line based execution
- Works on Linux/Unix systems
  
---
## Linux System Calls Used

#### File Operations

`open()`, `read()`, `write()`, `close()`, `stat()`

### Network Operations

`socket()`, `bind()`, `listen()`, `accept()`, `connect()`

### Process Management

`fork()`, `exit()`


## 📂 Project Structure
```
ConcurrentTCPFileTransferServer/
│
├── server.c      # Server application
├── client.c      # Client application
└── README.md

```

## 🖥️ Compilation & usage

### Compile server and client separately:
```
gcc server.c -o server
gcc client.c -o client

Step 1: Run Server
./server <port>
Example:
./server 9000

Step 2: Run Client
./client <server_ip> <port> <source_file> <destination_file>
Example:
./client 127.0.0.1 9000 demo.txt newfile.txt

```
## 🔒 Limitations

- No authentication or encryption
- Works for files accessible to server directory
- Designed for Linux/Unix environments

## 💡 Future Improvements

- Add multi-threading instead of fork()
- Add file upload support
- Add authentication

## 👨‍💻 Author

CR Dugade
Aspiring Software Developer

* GitHub: https://github.com/crd-codes
* LinkedIn: https://linkedin.com/in/chakradhar-dugade
* Email : crofficialuse@gmail.com 










