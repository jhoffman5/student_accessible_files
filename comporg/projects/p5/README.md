# p5 - NEON Intrinsics plus C++ 11 Threading

# Partnership Rules

We are using the following work rules:
- You may partner with whomever you choose.
- You may choose not to partner.
- You may work (share code) with one and only one person (your partner).
- You may organize help groups in any fashion you wish to discuss, draw pictures, research, etc.
- You may not use a projector to project code or otherwise share code outside of your partnership.
- Partners receive the same grade as each other.
- *Projects will be shifted to elearning as hand in projects.*
- Only one person in a partnership will submit code.
- Your code *must* indicate who your partner is at the top of your main source file.

# Command line options

```
hunchback p5 $> ./a.out -h
help:
-h       prints this
-s size  sets size (default is 128 - will be made divisible by 16)
-i iter  set iterations (default is 1)
hunchback p5 $>
```

```size``` is the number of floats that will be operated upon in 3 arrays. In your code, make sure that size is made to be a multiple of 16 if the user supplied value is not.

```iter``` is the number of times each version of the code you will write is run. You will use ```gettimeofday``` to get the time before starting a loop of ```iter``` times calling each version. After the last iteration, you will use ```gettimeofday``` a second time to compute an elapsed time for all of the repeated calls to your function. Then compute the average elapsed time. By looping a number of times, changes in machine load should average out.

# Step 1 - First version - just get basics working

You'll want these:

```C++
#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include <iomanip>
#include <cassert>
#include <arm_neon.h>
#include <vector>
#include <thread>
#include <sys/time.h>
#include <cstring>
```

You'll need to compile with something like this:
```
g++ -std=c++11 -pthread main.cpp
```

Later something like this:
```
g++ -std=c++11 -O3 -pthread main.cpp
```

Write a program that creates 3 float arrays of the size specified on the command line (after ensuring the size is a multiple of 16). I'll call these ```a```, ```b```, and ```c```.

Allocate these dynamically using a memory aligned version of ```malloc``` like so:

```c++
float * a = (float *) aligned_alloc(16, size * sizeof(float));
```

Remember to ensure that ```size``` is a multiple of 16.

While doing memory aligned allocs may not be strictly neccesary in this program, they often are in programs that use special instructions such as SIMD instructions. Now you know how to do that.

In ```main()``` call ```srand()``` with the current time.

Write a function that returns random numbers between 0 and 1 **inclusive**. 

Fill ```a``` and ```b``` with theese random numbers (between 0 and 1 inclusive).

Write a function that initialized one array to zero. Pass ```c``` to this function before launch each of what will become four loops (four different timing tests). This is to ensure that old summed values are not being reused.

I give you this function below:

```C++
void SingleCore(float * a, float * b, float * c, int size);
```

It adds each entry in ```a``` to the same entry in ```b``` and puts the result in the same slot in ```c```. This function will be your baseline for timing and also to calculate a known correct result.

Also write:

```C++
float SumOfSums(float * a, int size);
```

This adds up the first ```size``` floats at the given address and returns the sum. ```SumOfSums``` will be used to validate your later variations of ```SingleCore```.

Here is my ```SingleCore```:

```c++
void SingleCore(float * a, float * b, float * c, int size) {

	//cout << __FUNCTION__ << " " << hex << size << dec << " " << size << endl;
	assert((size & 0x7) == 0);
	size = size / 16;

	for (int i = 0; i < size; i++) {
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
	}
}
```

I have unrolled the loop to account for a guarantee of the length being a multiple of 16.
I specifically did this to provide a more *apples to apples* comparison to the SIMD instructions
which work on 4 floats in a row with one instruction. I unrolled my SIMD loop 4 times (4 x 4 == 16).

Call ```SingleCore``` to add ```a``` to ```b``` placing the result into ```c``` as stated above. Print out something like this:

```
hunchback p5 $> ./a.out -s 500000 -i 10
Array size: 500000 total size in MB: 5
Iterations: 10
Single core timings...
Naive: 0.002438 Check: 500289.843750
hunchback p5 $> 
```

This made arrays of 500000 floats (which is rounded up to a multiple of 16 if necessary) and then SingleCore was timed running 10 times.

The value after ```Check:``` is the result of the call to ```SumOfSums``` giving it the ```c``` from the last loop iteration. All subsequent ```Check:``` should produce the same value if your code is correct.

# Step 2 - SIMD

SIMD means *single instruction multiple data*. ARM offers the NEON instruction set. These are assembly language instructions that provide many of the same
operations as the standard instructions you've already used such as add, substract, multiply etc. 

However, the NEON instructions differ in an important way. They operate over several registers in parallel. In fact, the NEON instruction set adds a new set of registers to the ARM CPU designed for this purpose.

Intrinsics are proxies for assembly language instructions that are callable
directly from C and C++.

[Here](http://www2.tcs.ifi.lmu.de/~cichon/mca/2015/external/DEN0018A_neon_programmers_guide.pdf) is a link to a document describing NEON intrinsics (Chapter 4) and the whole underlying instruction set architecture. By the way, the only way these little ARM machines can process video so well is by virtue of extended instruction sets like NEON.

For example, ```vaddq_f32``` is a proxy for the ```VADD.F32``` instruction. This is the instrinsic used for this project.

To use an intrinsic in C or C++ we need new types. We are using floats, four at a time. The type that represents this is: ```float32x4_t```. Having the right type is necessary for both type checking purposes but more importantly in this case for computing the size (four floats). 

I am not going to tell you much about ```vaddq_f32``` other than it takes *floats (plural)* in ```a``` and ```b``` and returns *floats (plural)* for ```c```.

Write a function with the same signature as ```SingleCore()```.

```c++
void Intrinsic(float * a, float * b, float * c, int size)
```

Use instrinsics to duplicate the functionality of the ordinary version.

Now you should be able to produce this (compiled with ```-O3```):

```
hunchback p5 $> ./a.out -s 500000 -i 10
Array size: 500000 total size in MB: 5
Iterations: 10
Available cores: 4
Single core timings...
Naive: 0.002420 Check: 499957.687500
NEON:  0.002410 Check: 499957.687500
hunchback p5 $>
```

or this (compiled without ```-O3```):

```
hunchback p5 $> ./a.out -s 500000 -i 10
Array size: 500000 total size in MB: 5
Iterations: 10
Available cores: 4
Single core timings...
Naive: 0.008689 Check: 499725.843750
NEON:  0.004288 Check: 499725.843750
hunchback p5 $> 
```

# Step 3 - C++ Threading (C++ 11 and later)

C++ threading is an abstraction and wrapper of ```pthreads``` which is why it requires ```-pthread``` on the command line to compile properly. There are some wrinkles like all arguments to the thread worker are passed by copy. There is a way around this if you want to pass by reference. Notice, I designed the computation function to take points to the arrays so passing by reference is not used.

[Here](http://www.cplusplus.com/reference/thread/thread/) is a link to the cplusplus web site reference on C++ threads.

I am repeating their example here:

```c++
// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
 
void foo() 
{
  // do stuff...
}

void bar(int x)
{
  // do stuff...
}

int main() 
{
  std::thread first (foo);     // spawn new thread that calls foo()
  std::thread second (bar,0);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}
```

Launching a thread is as easy as making a thread object. The arguments to the thread constructor include the name of the thread worker and the arguments that should be passed to it. Notice the thread constructor has variable arguments. The thread constructor devolves into a template that matches the arguements to the thread worker against the signature of the thread worker. Being a template, if anything goes wrong you may get thousands of errors. Have fun with that.

You will launch as many threads as available cores. Get the number of available cores with ```hardware_concurrency()```.

Notice you have to ```join``` every thread you launch in order to release their completed spirit back to the universe. Since you don't know in advance how many cores you have, you have to store each thread in some kind of data structure. I used a vector. There may be some unexpected syntax problems in doing this. Tutorials online that are readily found give examples. Otherwise, it can be maddening because what *should* work doesn't.

You next write a loop that breaks down the total work into chunks and assign each chunk to a processor. If you have four cores, each core will do one quarter of the work.

*You must use the same computation routines that you have finished writing by the time you get here.*

Remember that your computing functions take addresses. Inside the loop starting one thread per core, factor this in to ensure each thread processes the right data.

## Here is a wrinkle...

You know the number of floats in the arrays are divisible by 16. The number of multiples of 16 may not be a multiple of the number of cores you have. You have to account for this. *At least one of your threads need to get a larger size than the others to account for any remainder.*

After dividing size by the number of core *that* result may not be a factor of 16. Therefore, you may need to shrink size a little more of each chunk sent to each core. *At least one of your threads need to get a larger size than the others to account for any remainder.*

At this point I have repeated *At least one of your threads need to get a larger size than the others to account for any remainder* twice. Just saying.

After getting multithreading working with the ```SingleCore``` function, you will be able to produce this:
```
hunchback p5 $> ./a.out -s 500000 -i 10
Array size: 500000 total size in MB: 5
Iterations: 10
Available cores: 4
Single core timings...
Naive: 0.008689 Check: 499725.843750
NEON:  0.004288 Check: 499725.843750
Threaded timing...
Naive: 0.006911 Check: 499725.843750
hunchback p5 $>
```

And finally, when completed for the NEON case:

```
hunchback p5 $> ./a.out -s 500000 -i 10
Array size: 500000 total size in MB: 5
Iterations: 10
Available cores: 4
Single core timings...
Naive: 0.008689 Check: 499725.843750
NEON:  0.004288 Check: 499725.843750
Threaded timing...
Naive: 0.006911 Check: 499725.843750
NEON:  0.005136 Check: 499725.843750
hunchback p5 $>
```

Now I want you to try out various sizes of arrays. Look for patterns. Note, when your arrays get big enough things will suddenly slow down a lot due to lack of memory on our systems.

```
hunchback p5 $> ./a.out -s 500 -i 10
Array size: 512 total size in MB: 0
Iterations: 10
Available cores: 4
Single core timings...
Naive: 0.000023 Check: 526.376465
NEON:  0.000009 Check: 526.376465
Threaded timing...
Naive: 0.000697 Check: 526.376465
NEON:  0.000293 Check: 526.376465
hunchback p5 $> ./a.out -s 5000 -i 10
Array size: 5008 total size in MB: 0
Iterations: 10
Available cores: 4
Single core timings...
Naive: 0.000232 Check: 5005.748535
NEON:  0.000098 Check: 5005.748535
Threaded timing...
Naive: 0.000471 Check: 5005.748535
NEON:  0.000342 Check: 5005.748535
hunchback p5 $> ./a.out -s 50000 -i 10
Array size: 50000 total size in MB: 0
Iterations: 10
Available cores: 4
Single core timings...
Naive: 0.001098 Check: 50085.875000
NEON:  0.000465 Check: 50085.875000
Threaded timing...
Naive: 0.001296 Check: 50085.875000
NEON:  0.000893 Check: 50085.875000
hunchback p5 $> ./a.out -s 500000 -i 10
Array size: 500000 total size in MB: 5
Iterations: 10
Available cores: 4
Single core timings...
Naive: 0.008681 Check: 499481.750000
NEON:  0.004309 Check: 499481.750000
Threaded timing...
Naive: 0.007025 Check: 499481.750000
NEON:  0.004278 Check: 499481.750000
hunchback p5 $> 
```
