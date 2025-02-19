- to begin acess https://github.com/thewh1teagle/zero-hid/tree/main
- after follow the steps on the readme.md
  - before processiding with the install make sure u have the file /etc/rc.local
  - if not do 'vim /etc/rc.local'
  - add a line exit 0
  - add #!/bin/bash
  - sudo chmod +x /etc/rc.local
  - sudo systemctl daemon-reload
  - sudo systemctl enable rc-local
  - sudo systemctl start rc-local
- after run script and add to the same file before what was added sudo
- now u can use the python3 scripts available



