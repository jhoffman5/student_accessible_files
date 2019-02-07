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

Unzip

Make:

```
qemu-system-aarch64 -M virt -m 1024 -cpu cortex-a53 \
  -kernel vmlinuz-4.9.0-8-arm64 -initrd initrd.img-4.9.0-8-arm64 \
  -append 'root=/dev/vda2' -drive if=none,file=hda.qcow2,format=qcow2,id=hd \
  -device virtio-blk-pci,drive=hd  -netdev user,id=mynet,hostfwd=tcp::2222-:22 \
  -device virtio-net-pci,netdev=mynet -nographic -smp 2
  ```
  
an alias
  
Ensure you have ```ssh```

Run the above in one terminal.

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
apt install wget
```

Download and unzip to a folder ```https://drive.google.com/open?id=1Y_KPUcv0wIdsBpqeRnS9CpfOKRs4naUb```

Use wget if you want this INSIDE your WSL environment. This is optional.

Make:

```
qemu-system-aarch64 -M virt -m 1024 -cpu cortex-a53 \
  -kernel vmlinuz-4.9.0-8-arm64 -initrd initrd.img-4.9.0-8-arm64 \
  -append 'root=/dev/vda2' -drive if=none,file=hda.qcow2,format=qcow2,id=hd \
  -device virtio-blk-pci,drive=hd  -netdev user,id=mynet,hostfwd=tcp::2222-:22 \
  -device virtio-net-pci,netdev=mynet -nographic -smp 2
  ```
  
an alias

# Making the alias

In your home directory (under WSL on Windows) there is or should be a file called ```.bashrc```. If it isn't there, make it.

Go to bottom.

Add:
```
alias ARM=`qemu-system-aarch64 -M virt -m 1024 -cpu cortex-a53 \
  -kernel vmlinuz-4.9.0-8-arm64 -initrd initrd.img-4.9.0-8-arm64 \
  -append 'root=/dev/vda2' -drive if=none,file=hda.qcow2,format=qcow2,id=hd \
  -device virtio-blk-pci,drive=hd  -netdev user,id=mynet,hostfwd=tcp::2222-:22 \
  -device virtio-net-pci,netdev=mynet -nographic -smp 2`
```

Write - exit. Then ```source .bashrc```
