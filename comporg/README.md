# Temp home for Comp Org

# Both Mac and Windows

username is ```user```.
password is: ```a```

This is also root's password.

# Mac

```
brew install qemu
```

Download and unzip to a folder ```https://drive.google.com/open?id=1Y_KPUcv0wIdsBpqeRnS9CpfOKRs4naUb```

Add this to your ```.bashrc``` in your home directory:

```
alias ARM='qemu-system-aarch64 -M virt -m 1024 -cpu cortex-a53 -kernel vmlinuz-4.9.0-8-arm64 -initrd initrd.img-4.9.0-8-arm64 -append "root=/dev/vda2" -drive if=none,file=hda.qcow2,format=qcow2,id=hd -device virtio-blk-pci,drive=hd -netdev user,id=mynet,hostfwd=tcp::2222-:22 -device virtio-net-pci,netdev=mynet -nographic -smp 2'
```
  
After you have done this, do ```source .bashrc```.

Ensure you have ```ssh``` by typing same. If the command is not found do ```apt install ssh```.

Run the above in one terminal. ```ARM```

Open another terminal and

```ssh user@localhost -p 2222```

# Windows

Install Linux ON Windows - WSL. I used Debian because of size. All distributions at the Microsoft store should work.

Launch your Linux command line.

```
sudo apt install qemu
```

or 

```
su
apt install qemu
apt install ssh
```

Download and unzip to a folder ```https://drive.google.com/open?id=1Y_KPUcv0wIdsBpqeRnS9CpfOKRs4naUb``` as you would normally in Windows. 

In your Linux subsystem add this to your ```.bashrc``` in your home directory:

```
alias ARM='qemu-system-aarch64 -M virt -m 1024 -cpu cortex-a53 -kernel vmlinuz-4.9.0-8-arm64 -initrd initrd.img-4.9.0-8-arm64 -append "root=/dev/vda2" -drive if=none,file=hda.qcow2,format=qcow2,id=hd -device virtio-blk-pci,drive=hd -netdev user,id=mynet,hostfwd=tcp::2222-:22 -device virtio-net-pci,netdev=mynet -nographic -smp 2'
```

Write - exit. Then ```source .bashrc``` in your Linux shell.

Ensure you have ```ssh``` by typing in same. The command should be found (as you installed it above).

Run the above in one Linux shell. ```ARM```

Open another terminal and

```ssh user@localhost -p 2222```

# VISUAL STUDIO CODE Integration

Add this to your Visual Studio Code:

```
https://marketplace.visualstudio.com/items?itemName=lukasz-wronski.ftp-sync
```

Configure it to use ```user@localhost``` as the user, ```a``` as the password and to use port number ```2222```.

Then, you can edit in Code on Windows or the Mac and every time you save the file it will be ftp'd over to the ARM VM.


