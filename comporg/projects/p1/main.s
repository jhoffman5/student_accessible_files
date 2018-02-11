/*
Hello World written in AArch64 assembly language (gcc compatible).

Perry Kivolowitz - Professor - Computer Science
Carthage College

For reference purposes the following:

ARM (A64) From Wikipedia

The 64-bit ARM (AArch64) calling convention allocates the 32 ARM registers as:

x30 is the link register (used to return from subroutines)
x29 is the frame register
x19 to x29 are callee-saved
x16 to x18 are the Intra-Procedure-call scratch register.
x9 to x15: used to hold local variables (caller saved)
x8: used to hold indirect return value address
x0 to x7: used to hold argument values passed to a subroutine, and also hold results returned
from a subroutine.
The last register, stack pointer and zero register is referenced either as sp or xzp.
All registers starting with x have a corresponding 32-bit register prefixed with w. Thus, a
32-bit x0 is called w0.
*/

	.arch	armv8-a
	.file	"main.s"

	/* The text section is written to the executable file. When loaded for execution it
	   is marked as read-only. Why?
	*/

	.text
	.align	2
	.global main

main:

	str	x30, [sp, -16]!	// We are running in the environment of the standard C
						// runtime. This means, our main was called by _main to
						// which we must return.

						// When our main is called, the address to which we
						// should return is in X30. This first statement in the
						// program is to preserve this address on the stack.

	ldr	x0, =s			// Load the address of the hello world string into x0.
						// It is the first argument to the function call puts().  

	bl	puts			// Call puts. puts() is coming from the C runtime library which is 
						// linked to our program by default by gcc. Invoking bl causes the
						// address of the next instruction to be placed in x30. The called
						// subroutine will preserve this address. Do its thing. Then restore
						// this address into x30 and ret.

	mov	x0, xzr			// Our main returns a result code where 0 means all went
						// well. This result code goes back in x0.

	ldr	x30, [sp], 16	// When we started, the address to which we must return was in
						// x30. Our first job was to preserve this address on the stack.
						// Here, the address is removed from the stack and placed back in
						// x30. This also undoes the change in the stack pointer.

						// Just imagine what would happen if the value of the stack pointer
						// was not exactly correct... Well? What would happen? Seriously.
	ret

	/* The data section is written to the executable and represents your global and / or
	   static variables. Why?
	*/

	.data

	/* You will note two things about this string. First, there is no terminating null.
	   The terminating null is provided by the assembly language directive .asciz.
	   Second, there is no new line at the end of the string. This is provided by the
	   C runtime library call puts.
	*/

s:	.asciz	"Hello, world! (From ARMV8 - 64 bit - assembly language)"

	.end
