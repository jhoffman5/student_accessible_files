# Other Instructions and Tips

# Test bit and branch

```tbz	rn, bit number, label```

```tbnz	rn, bit number, label```

# #define equivalent

Useful for struct offsets is ```.equ```.

```.equ	ADDR_SIZE, 8```

# Macros

```
.macro HW, label
		ldr	x0, =\label
		bl	puts
.endm
```

The first argument is the macro name. Then, macro arguments. Use the arguments by prepending "\\".

# Conditional assembly

Like in the C preprocessor but different.

```
.ifdef
.ifndef
.else
.endif
```

# Initializing memory with a value

```.space``` reserves a certain number of bytes that are initialized to zero.

```.quad value``` reserves 8 bytes and fills with value.

```.word value``` reserves 4 bytes and fills with value.

```.hword value``` reserves 2 bytes and fills with value.

```.byte value``` reserves 1 byte and fills with value.

# Jump tables

Jump tables are cool. Internally, system calls and interrupts will use jump tables. Methods of a class are dispatched kind of like this too.

A jump table is a table of addresses (8 bytes each, of course). An index is used to reach into the table and pull out one of the addresses which is jumped-to or called as a subroutine.

Here is a jump table:

```
		.data
		.align	8
BoxJumpTable:
		.quad	BoxVolume
		.quad	BoxPrint
		.quad	0
```

Here is how one would call Box::BoxPrint(this):

```
		ldr			x0, =box
		mov			x1, BOX_PRINT
		ldr			x2, =BoxJumpTable
		ldr			x2, [x2, x1, lsl 3]
		blr			x2
```

This code assumes that BOX_PRINT is an ```.equ``` with value 1. Also, ```box``` is a range in memory containing a box's dimensions (width, height, depth).

# Visual mode for gdb

```
layout split
layout regs
```
