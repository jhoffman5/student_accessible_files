# Keep your repos to yourselves

# Directories

**You must have a folder named ```networking```. This directory must have mode 700 as 
in ```chmod 700 networking```. Inside this folder there must be a directory named P2.
It is in P2 that you leave your project.**

**DO NOT MODIFY ANY OF YOUR FILES IN THIS FOLDER AFTER THE DUE DATE**

# PROJECT 2 - TCP

In this project, you will write a *single threaded* TCP server and client to
exchange information.

The client will take a **text file name** as a command line option, open the
file, and send the file's contents to the server. The client then waits for a response 
from the server. When the response is received, its text is printed.

The server will wait for connections. Upon accepting a connection, the server
will receive the text sent by the client. The server 
will count the number of lines in the file and the number of instances of the letters
corresponding to the common vowels ("aeiou", never "y"). 

The server will send a report back
to the client. Also, it will print some information to its own console.

With regard to counting  vowels I am placing a non-networking related constraints
upon your work. This is in recognition of your status as advanced CS students and my
desire to teach craftspersonship.

The additional constraint are these:
* You cannot use an if statement in the code that counts vowels. A ```switch``` statement qualifies as if statements.
* You cannot use sets or other template-based data structures provided by C++.

So, code like:

```
if (input[i] == 'A' || input[i] == 'a')
   a_counter++;
```
or

```
counters['a']++;	// counters is an STL container.
```

is prohibited. However, you can use an ```if``` statement with ```isalpha``` if you wish. This:

```
if (isalpha(input[i])) {
   // etc
```

is permitted.

# Goals of the project

This project teaches a number of things.

1. The nature of connection-based network communications using reliable protocols like TCP.
2. Writing a TCP client.
3. Writing a single threaded TCP server.
4. More \*nix including ```GDB```.

# Adherence to this specification

You must adhere **completely** to this specification in every respect. Down to each
letter and space, your code must behave **exactly** like mine. Any deviation is 
considered an error and will result in grade reductions.

Repeat, you have **NO** latitude what-so-ever in what you:
* name your source code file or files
* what you output
* what options you process
* nothing

In the event that *my* code does not adhere to this specification, the code supercedes
the specification. Also, please let me know.

# Pre-existing client and server

You are given in executable form, my own client and my own server to test against. This means you can pick one or the other to write yourself first instead of having to write both at the same time.

# Client program

## File names

Your client program file name must be ```client.cpp```. Your entire program must be
implemented in one file. 

## Command line options

You will use getopt to implement command line options. These are:

* ```-h```
This prints the help text you will find below. Your help text must be exactly as given.
No differences of any kind are permitted. Exit, after the help text is printed.

* ```-d```
If present, you can switch on any debugging features you might necessary. I will not
be testing this. This is only for you. If given, turns on any debugging features you wish to add. 
   This is handy rather than
changing the program to turn on and off debugging features and having to recompile.
In the general case, remember checking the debugging option slows down your code.

* ```-f file_name```
The project is based on sending a text file to the server and getting information back.
This is how you specify the name of the file to use. **This option is required**.

* ```-s server_ip_address```
The default server IP address is 127.0.0.1.

* ```-p port_number```
The default port number is 5077. If you need to override this, you can specify a 
different port number in this way. At some point you will need to override the default because only one student can be testing on the same port at a time.

You must match the following output from ```-h```:

```
options:
	-h displays help
	-d debug mode
	-f file to send (must be text file)
	-s server_address ... defaults to 127.0.0.1
	-p port_number ... defaults to 5077
```

When you exit, use return code 0.


## Testing your client

You must run a server first. It will listen for connections and respond.

Send a tiny test file to the server. The server will accept the file and process it. It will count lines and vowels and send back a report. Your client prints the report.

For the tiny file, create something with easily verified contents. Given the same file, all programs should produce the same values.

Here is a sample server output:
```
Server bound on port 5077
Server received connection from 127.0.0.1 on port 21998
Server expecting to receive a file with 150 bytes.
Server about to send 36 bytes to client at 127.0.0.1
Server closing connection with: 127.0.0.1
```

Here is a sample client output for the same file:

```
Client read input file: makefile and closed it
Client sent file with: 150 bytes
Client ready to receive length of 36 bytes.
Lines: 12
A: 5
E: 10
I: 3
O: 2
U: 0
```

By creating and using your own tiny text file, you can easily determine if the report is correct.

When you gain confidence, try larger and larger files. If the file is text, there should be no practical limit to the size of the file sent.

## Error conditions and exit codes

Pay attention to this. These are hints of what to look for. Failure to check for these errors could result in point deductions.

The *sample output statements* are only that, samples. These come from my own source code so reflect my own variable naming, etc. 

| Sample output statement | Exit Code |
|:----------------------- |:---------:|
|cerr << "-f must be supplied" << endl;| 1|
|perror("Client could not open file for reading:");|1|
|perror("Client failed to open socket");|2|
|cerr << "Client failed in gethostbyname()" << endl;|3|
|perror("Client connection failure:");|4|
|cerr << "Client sent wrong number of bytes for file length: " << bytes_sent << endl;| 5|
|cerr << "File read failed" << endl;| 6|
|cerr << "Client sent wrong number of bytes in sending file: " << bytes_sent << endl;| 7|
|cerr << "Client received wrong number of bytes for size of long expected " << sizeof(long) << " bytes got " << bytes_read << " bytes" << endl;| 8|
|cerr << "Client received wrong number of bytes in return. Expected " << file_size << " bytes but got " << bytes_read << " bytes" << endl;| 9|

# Server Program

The server program must be run before your client program to work properly. To force some of the errors below, 
you must violate this.

In this project, a server can
service only one client at a time. Attempting to contact a busy server will result in an
error condition which your client must handle gracefully (see Error Checking).

## Command line options

You must support the following command line options:
* ```-h```
Displays help information and exits. See additional information in the description
of the Client program.

* ```-d```
If present, you can switch on any debugging features you might necessary. I will not
be testing this. This is for you.

* ```-p port_number```
The default port number is 5077. If you need to override this, you can specify a 
different port number in this way.

You must match the following output from ```-h```:

```
options:
   -h displays help
   -d enables debugging features
   -p port_number ... defaults to 5077
```

## File names

Your server program file name must be ```server.cpp```. Your entire program must be
implemented in one file.

## Testing your server

Your server will have to work against your own client, of course. It will have to work *identically* against mine.

## Error checking and exit values

Pay attention to this - it gives hints about error conditions you should be checking for.
Failure to check for these errors will result in point deductions.

## Error conditions

| Sample output statement | Exit Code |
|:----------------------- |:---------:|
|perror("Server failed to open socket");| 1|
|perror("Server bind failed:");|2|
|perror("Server listen failed:");| 3|
|perror("Server accept failed:");|4|
|cerr << "Server attempting to read file name length expected " << sizeof(long) << " bytes got " << bytes_read << " bytes" << endl;|no exit|
|cerr << "Server received wrong number of bytes. Expected " << file_length << " bytes but got " << bytes_read << " bytes" << endl;|no exit|
|cerr << "Server sent wrong number of bytes for reply length. Expected: " << sizeof(long) << " got " << bytes_sent << endl;|no exit|
|cerr << "Server sent wrong number of bytes for reply. Expected: " << reply_size << " got " << bytes_sent << endl;|no exit|

# Framing

*TCP is a "stream" protocol - this does NOT mean it is used for streaming.*

The bytes you get from a TCP socket are in one long logical stream. There are no beginnings and no endings except the first and last bytes. Compare this to UDP where every datagram had its own beginning and ending.

To break a TCP stream into logical chunks you need to implement some form of *framing*. Framing frames. It is used to tell you where one logical chunk starts and where one ends. In this program we have only one logical chunk flowing back and forth in each direction. From client to the server the one chunk is the file. From the server to the client, the one chunk is the report.

We can get by with a framing technique whereby the length of the chunk is sent (in binary) before the chunk. Because the length is a fixed length, the other end knows exactly how many bytes to read and how to parse what its read. Following the length comes that many bytes of chunk.

In this program the data type of the length is ```long```.

In the above example, the client would have sent this:

| 8 bytes containing the value 150 | 150 bytes containing the contents of the file |

Questions for you: htons (16 bits). htonl (32 bits). The lengths are 64 bits. What to do? What to do?

# Allocating and releasing memory

Points will be deducted if there is any way to leak memory. In general in virtually all cases anything
you allocate with ```new``` or ```malloc``` must be freed with ```delete``` or ```free```
respectively.

# Handy links

[A fairly complete cheat sheet](http://beej.us/guide/bgnet/html/single/bgnet.html "Beej")

# What to turn in

**Nothing** - don't turn in anything. Leave your code in exactly the place specified at the top
of this document. **DO NOT MODIFY ANY OF YOUR FILES IN THIS FOLDER AFTER THE DUE DATE.** Doing
so leads to a score of zero.


