# Floating point instructions (and curses)

In this project you will make use of floating point instructions as well as the floating point register set. The output of your calculation will be aided by use of the curses library.

# Install ncurses

Become root using ```su```. Then use apt to install ncurses.

```
su
apt install libncurses-dev
```

# What the program does

This program calculates the values of a sine wave. It scales and converts the sine values to a range of 0 to 9 and uses this to choose a single ASCII character approximating a relative brightness. Putting this in motion, you'll get a crude sine wave animation on screen.

The program is terminated when you abort it with CONTROL-C.

For fast performance, simply use a ```bash``` window that is small - such as 80 by 24. For examining your lovely results in detail, simply make your ```bash``` window full screen and run the program again.

# The C version

You are given a version of the program written in C in the style of assembly language. This is that last time C source code will be given to you.

Compile with:

```
gcc main.c -lcurses -lm
```

The first link library is to get the curses code. The second is to get the math code (providing *sin*).

A working (though not necessarily current) version is printed here:

```c
#include <curses.h>
#include <unistd.h>
#include <math.h>

char * levels = " .:-=+*#%@";

int main()
{
	initscr();
	double tpi = 3.14159265359 * 2;
	double phase = 0;
	double theta = 0;
	double increment = tpi / (double) COLS;
	int l;
	int c;

top:	erase();
	phase += increment;
	l = 0;
sinner:	if (l >= LINES) goto bottom;
	theta = 0;
	c = 0;
tinner:	if (c >= COLS) goto binner;
	int intensity = (int) ((sin(phase + theta) + 1.0) / 2.0 * 10);
	mvaddch(l, c, levels[intensity]);
	theta += increment;
	c++;
	goto tinner;

binner:	l++;
	goto sinner;

bottom:	box(stdscr, 0, 0);
	refresh();
	goto top;

	endwin();
	return 0;
}
```

Notice there are no higher level constructs such as for loops or braces (apart from the beginning and ending brace). I've told you that C is high level assembly language... here is more evidence supporting this claim.

This program is terminated by aborting it with Control-C.

# Project

You are to translate this C version into AARCH64 assembly language.

You *must* use floating point instructions with the exception of the *sin* calculation. The AARCH64 ISA doesn't have a *sin* instruction so instead use the math library version.

You must use floating point registers (S registers and / or D registers) in order to make use of the floating point instruction set. S is single precesion (float). D is double precision (double). We're using all doubles in this project.

Correct backing up and restoring of registers are required. 

# Reference

AARCH64 floating point instruction reference:

[Here](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0802b/a64_float_alpha.html)

Instructions you'll care about include the obvious add, divide and multiple. But also consider that you are converting from float to int at least once. There is an instruction for this purpose.

Information about floating point registers can be found:

[Here](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/ch04s06s01.html)

# Lecture on floating point operations

There will be no lecture on this. See **Reference**. Everything you need to know is there and here.

# Partner Rules

No partners. All work is solo.

# Support from instructor and tutor

You must function more autonomously on this project. Your instructor and tutor will be less helpful than on previous projects. They will provide only cryptic hints and nudges.




