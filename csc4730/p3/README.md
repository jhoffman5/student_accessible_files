# CSC 4730 - Project 3

In this project you will take xv6 where you left off (you added a guard page) and rearrange a process' address space to conform to the more typical layout. In the image below on the left, is where you left things at the end of P2. On the right is how it will look when you are done with this project, p3.

![xv6_move_stack](./xv6_move_stack.png)

Note: in the xv6 kernel what I labeled as ```HIMEM``` is called ```USERTOP```.

## Discussion

You saw in ```fork()``` how a new process's address space is initialized with a copy of the parent process. You figured out that you had to avoid copying any pages full of dragons. You'll definitely need pay to attention to how address spaces are copied in this project as well. Stay away from dragons.

When you added the guard page in ```exec()``` you did so by starting ```sz``` at 0x1000 instead of 0. You also saw that ```sz``` continually got bumped down into higher memory as the address space was initialized. Ultimately, ```sz``` came to represent the place where the heap stopped and dragons started (in the diagram on the left).

In ```exec()```, figure out how to move the stack to the last page of user memory - in the xv6 kernel the top of user memory is called ```USERTOP```. By moving the stack to the top of memory the heap will start immediately after the code / globals. You still need to keep track of where the heap ends and the dragons begin, which is what ```sz``` is designed to do. 

You might think heap growth is all done. But. No.

There is some additional work for growing the heap (and later, growing the stack). **You must ensure that the heap and stack do not collide.** You do this by keeping the two at least one page apart. You will have to check for this during heap growth and stack growth. Start by figuring out ```sys_sbrk()``` in sysproc.c and ```growproc()``` in proc.c. Then when you understand how the heap grows (and how to check for collision with the stack) you will be better able to implement stack growth (and how to check for collision with the heap).

(Darn! ```sz``` is referred to all over the place. I guess you’ll have to track down every one and see if any of them needs changing.)

Now you have two regions of memory that can change size. ```sz``` is keeping track of one of them. You will need another variable to keep track of the stack size. Gee, wouldn't it be nice to have a place to put metadata relating to a process?

What about stack growth? It DOESN’T HAPPEN ON PURPOSE – rather it just happens as code is executed. Rather than knowing ahead of time that you want to add memory you’ll have to wait for a SEGFAULT. Ow. Somebody poked a dragon! 

Better look up SEGFAULT which is called ```T_PGFLT``` in xv6. ```T_PGFLT``` is of course, *a trap*.

But not just any SEGFAULT. If it happens within the two pages that’s just above your stack then it might have happened because the stack needed to grow. If it happens anywhere else in unallocated space – unleash the dragons (that’s what happens now). 

Again, make sure you leave a page between the lowest stack page and the highest heap page.

Damn you Perry. By now you have figured out there doesn't seem to be any code implemented to handle page faults. Maybe you need to implement this code. Where? I keep saying *it is a trap*. 

Think about what happens when you pass a parameter into the kernel, for example; if passing a pointer, the kernel needs to be very careful with it, to ensure you haven't passed it a bad pointer. Remember this from a few paragraphs above: *(Darn! ```sz``` is referred to all over the place. I guess you’ll have to track down every one and see if any of them needs changing.)*

## How to test your program

You must write a number of simple user land test programs. Failure to write these (and write them well) will probably result in a very very low grade.

### Did the stack move?

Print out the address of a local variable. It better be close to the top of memory.

### Can the stack grow?

Create a function that is a little bit recursive (descends a controlled number of levels). In the function have a large local variable - for example a 1K ```char``` buffer. Print out each time you enter the function to get an idea how much the stack has grown.

### Does the stack collide with the heap?

Do the above enough times (descend enough times) you should crash. The number of times you recurred times the size of the big local variable should make sense.

### Does the heap collide with the stack?

Malloc a 1K array over and over printing out as you go so you get a sense of when you run out of memory.

## What do hand in?

Zip up your whole xv6 folder and submit to schoology.

## Partner rules

Have a partner. Only one partner submits code. The other submits a text file saying who the other partner is. The submitting partner must also name the non-submitting partner.

## Academic honesty caveat

I may look closely for duplicated code if I catch a whiff of impropriety.
