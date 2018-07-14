# Let's play

Almost every first look at a programming language starts with a simple program that prints "hello, world". It's a tradition. Here is the original from 1974 by Brian Kernighan, an author of the C programming language:

```c
#include <stdio.h>

main( )
{
        printf("hello, world\n");
}
```

We're not going to follow tradition.

Instead, we are going to start day 1 with something more sophisticated and just play with it. 

# Our development environment

After installing our development environment, start the VirtualBox (VB) Manager. Note your windows will differ slightly from the following:

![VBManager](./img/vbmanager.png)

You will have only one Virtual Machine (VM) named ```cccsdev``` for Carthage College Computer Science Development. Notice it says it is powered off. Double click on it - a old timey looking screen will come up, just hit the return key. Wait a bit and you'll see this:

![Starting Screen](./img/starting_screen.png)

Double click on ```Visual Studio Code```. All your programming work will be done in this program.

Use the File --> Open Workspace menu command shown here:

![Open Workspace](./img/open_workspace.png)

Navigate to ```ascii```. ASCII stands for American Standard Code for Information Interchange. Computers don't know about letters natively - only we do. ASCII is a code for mapping numbers to letters.

![Navigate to ASCII](./img/navigate_to_ascii.png)

Don't go into any of the ```.template``` folders. There's nothing that interesting there. Really.

Double click on the workspace file. Each of your projects (that you'll create in the future) will have a workspace file with a name you pick prepended.

![Double Click on Workspace](./img/select_workspace_file.png)

There's a good chance your next screen will be a welcome screen from VSCode. If it is, just close it by clicking on the ```x``` on the tab, not at the upper right of VSCode (that one will close the program). The icon in the dark area at left that looks like multiple pages can be clicked upon to view the files that make up your workspace. If ```main.cpp``` isn't already visible, double click on its name.

![Code](./img/code.png)
