# AARCH64 assembly language on an x86 linux machine

If you have an Intel-based Linux machine, here is how you can use it to develop and test AARCH64 assembly language pojects.

Install the following:

```
sudo apt-get install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
sudo apt-get install qemu qemu-user-static
```

Then you can assemble and link ```main.s``` with:

```
aarch64-linux-gnu-gcc main.s
```

And execute with:

```
qemu-aarch64-static -L /usr/aarch64-linux-gnu/ ./a.out
```

# Files for Computer Organization

## Projects

### p1

p1 is [here](./projects/p1)

### p2

Enumerate argv. p2 is [here](./projects/p2)

### p3

Sorted singly linked list. p3 is [here](./projects/p3)

## Teaching materials

### regs

Teaches which registers should be saved by you and which you can assume will be blown away.

### if / else

[A video on if / else](https://www.vimeo.com/203879694)

[A video on if](https://vimeo.com/203882389) *Can you spot the little bug?*

### argc, argv

A **general** video on argc and argv - not relating to 2510 specifically.

### for loops

[for loop video](https://vimeo.com/203891390)

### structs right and wrong

[wrong](https://vimeo.com/205230764)

[right](https://vimeo.com/205235384)

