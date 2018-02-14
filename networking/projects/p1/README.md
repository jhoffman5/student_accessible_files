# Directories

**You must have a folder named ```networking```. This directory must have mode 700 as 
in ```chmod 700 networking```. Inside this folder there must be a directory named P1.
It is in P1 that you write your project.**

**DO NOT MODIFY ANY OF YOUR FILES IN THIS FOLDER AFTER THE DUE DATE**

# PROJECT 1 - UDP

In this project, you will write a UDP client and server to exchange information. 
The client will blast UDP datagrams at the server. The server will modify each
received datagram and return it to the client.

UDP is the User Datagram Protocol. It is a best effort protocol which makes no
guarantee of order of delivery or even delivery at all. For example, the client
has no idea if there even *is* a server at the other end.

This project teaches a number of things.

0. Systems programming.
Systems programming is different from all the programming you may have done
in your career so far. It is down, dirty and dangerous.

1. Initializing a UDP client and server using Berkeley sockets.
Berkeley sockets are required knowledge, in my view, if you are going to 
learn about network programming. Modern languages have lots of higher level
abstractions to hide the details you are learning here.

2. Working with pointers, unterminated buffers and pointers. Also pointers.
Systems programming. It's what's real. No safety nets here.

3. Byte ordering differences on different architectures.
You will code your projects on the ARM machine and on an Intel machine. You should test Intel / Intel, Arm / Arm and Intel / Arm.

You will be running on the same internal Carthage network. As such, the connections
will appear to be more reliable than UDP really is. That's why the client is going
to send datagrams to the server as quickly as it can. 

Maybe your client machine will
be slow (other users on it). Maybe the server machine will be slow (other users on
it). I am hoping you will experience datagram loss.

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
the specification. Also, please let me know because clearly I made a mistake that I would like to fix.

# Client program

You have no lattitude with respect to datagram format, options supported, help text 
and program function.

The client program will send a fixed number of properly initialized ClientDatagram
packets to the server. In a perfect world the client program will receive back the
same number of ServerDatagrams. 

Each pair (client to server datagram is expecting a matching server to client datagram)
is associated with one another using a
```sequence_number``` member. As the client transmits, it memorizes that it sent that
particular sequence number. As it receives acknowledgements, it removes its memory of
that sequence numbers.

If an acknowledgement is received for a sequence number you have no record of or no
longer have a record of, you should stop the program with specific error values (may
not be altered).

After sending a fixed number of datagrams, try receiving 1000 more times to collect
any straggler responses. Then, print status information (must match the specification)
which will list the number of packets send and how many packets did not receive an
acknowledgement. 

Many error conditions must be checked. They must be handled in specific ways. The
C runtime call ```exit()``` accepts a parameter which is the return value of your
whole program. My testing programs will respond to the specific return values of
your code.

## File names

Your client program file name must be ```client.cpp```. Your entire program must be
implemented in one file. You must use ```structure.hpp``` and ```defaults.hpp``` as
given.

## Command line options

You will use getopt to implement command line options. These are:
* ```-h```
This prints the help text you will find below. Your help text must be exactly as given.
No differences of any kind are permitted. Exit, after the help text is printed.

* ```-d```
If present, you can switch on any debugging features you might necessary. I will not
be testing this. This is for you.

   If given, turns on any debugging features you wish to add. This is handy rather than
changing the program to turn on and off debugging features and having to recompile.
In the general case, remember checking the debugging option slows down your code.

* ```-s server_ip_address```
The default server IP address is 127.0.0.1. This address is your machine. To specify
my machine, use 10.250.0.108.

* ```-p port_number```
The default port number is 39390. If you need to override this, you can specify a 
different port number in this way.

You must match the following output from ```-h```:

```
./client options:
	-h displays help
	-d debug mode
	-s server_address ... defaults to 127.0.0.1
	-p port_number ... defaults to 39390
```

When you exit, use return code 0.

## Client Datagram

The client datagram is the one that the client sends to the server. It is found in
```structure.hpp```. You may **not** alter this structure in **any way**.

```
#pragma once
/* Reminder - you may not deviate from this in any way. */

/* Client Datagram Specification.

sequence_number 	is an unsigned int. You must keep track of every
sequence_number you have sent. The server will return packets matching 
each sequence number it receives. The output of your client is a count
of sequence numbers you have sent but not received back.

payload_length		is an unsigned short. Recall that shorts are 16
bits in length. This value shall indicate the number of bytes in the
payload. Notice the payload member is a char - clearly this isn't the
real payload since the real payload can be more than one byte. The real
payload is allocated at payload_length so its beginning address is the
address of the payload member.

payload_length may be 0 to 999.

payload			this member is a placeholder. Use this member
as a means of finding the first byte of the actual payload. The value
of the payload your Carthage email name. For example, for me the
exact structure I would send for sequence number 3 is:

four bytes containing 3.
two bytes containing 11.
eleven bytes containing pkivolowitz

This is a total of 19 bytes.

Nineteen? Six plus eleven in 17 not 19. Yet, the right answer is
19 on x64 and AArch64. Wow. Mind blown. Why?

PAY ATTENTION - many of you will screw managing the memory for 
the client datagram.
*/

struct ClientDatagram
{
	unsigned int sequence_number;
	unsigned short payload_length;
};

/*	Server Datagram Specification

The structure of the datagram returned from the server back to the 
client in response to the server receiving a client datagram of the
same sequence number.

datagram_length		is the number of bytes in the entire client datagram.
Not the payload_length from the client datagram, its entire length. In
my example, the right value is 19.
*/

struct ServerDatagram
{
	unsigned int sequence_number;
	unsigned short datagram_length;
};
```
You must send exactly ```NUMBER_OF_DATAGRAMS``` packets. This means you must be
prepared to keep track of the status of that many. However, for debugging purposes
you might want to send a very small number of packets so that you aren't overwhelmed
by debugging output. Second hint, you probably want debugging output. Use the ```-d```
option to turn on and off the debugging output easily.

## Testing your client

You must run a server first. It will listen for packets and respond.

You must test your client against your own server. And you must test your client against my server.
My server will be running at IP address: ```10.250.0.108```. This is why you must support the
```-s``` option.

## Error checking and exit values

Pay attention to this - it gives hints about error conditions you should be checking for.
Failure to check for these errors will result in point deductions.

| Sample output statement | Exit Code |
|:----------------------- |:---------:|
|cerr << "ERROR wrong datagram_length: " << v << " should be: " << datagram_length << endl; <br/>cerr << "Sequence number: " << sequence_number << endl;| no exit |
|cerr << "Unable to allocate space for buffer: " << datagram_length << " bytes." << endl;| 4 |
|perror("ERROR opening socket");| 1 |
|perror("ERROR setting nonblocking");| 2|
|cerr << "ERROR, no such host: " << server_address << endl;| 3|
|cerr << "ERROR Number of bytes sent [" << bytes_sent << "] does not match message size [" << datagram_length << "]" << endl;| 5|
|cerr << "ERROR failure in packet reception" << endl;|6|

# Server Program

The server program must be run before your client program. A properly written server
can service multiple clients at the same time since datagrams do not have any sense
of persistant connection. Everything the server needs to know to acknowledge a packet
is contained in the received packet (and associated metadata).

Upon receiving a packet from a client, the server attempts to interpret the bytes as
a ServerDatagram. It will create an ackknowledgement by sending back the same 
sequence number contained in the received packet. It also sends back the total 
number of bytes in the received datagram. In other words, the number of bytes returned
by recvfrom.

**Unlike the client**, the server can block on reads. Servers respond to client requests.

## Command line options

You must support the following command line options:

* ```-h```
Displays help information and exits. See additional information in the description
of the Client program.

* ```-d```
If present, you can switch on any debugging features you might necessary. I will not
be testing this. This is for you.

* ```-p port_number```
The default port number is 39390. If you need to override this, you can specify a 
different port number in this way.

You must match the following output from ```-h```:

```
./serveroptions:
   -h displays help
   -d enables debugging features
   -p port_number ... defaults to 39390
   -v verbose mode - prints the received payloads
```

## File names

Your server program file name must be ```server.cpp```. Your entire program must be
implemented in one file. You must use ```structure.hpp``` and ```defaults.hpp``` as
given.

## Server Datagram

The server datagram is the one that the server sends back to the client. It is found in
```structure.hpp```. You may **not** alter this structure in **any way**. You can see
it above in the discussion about the client datagram.

The server datagram needs no special memory tricks as it is a fixed size.

## Testing your server

Your server will have to work against your own client, of course. 
I will also provide an ARM version of my client. Your server must support my client.

## Error checking and exit values

Pay attention to this - it gives hints about error conditions you should be checking for.
Failure to check for these errors will result in point deductions.

| Sample output statement | Exit Code |
|:----------------------- |:---------:|
|perror("ERROR opening socket");|1|
|perror("ERROR on binding");|4|
|cerr << "ERROR in sendto to: " << buffer << endl;<br/>perror("ERROR in sendto:");|no exit|


# Allocating and releasing memory

Points will be deducted if there is any way to leak memory. In virtually all cases anything
you allocate with ```new``` or ```malloc``` must be freed with ```delete``` or ```free```
respectively.

# Sending and receiving must happen in an asynchronous manner

Your client program will be sending as fast as possible. The server will be responding
as quickly as it can. Both sides have a fairly limited number of packets they can buffer
before dropping them. Therefore, you must interleave transmission with reception. 

Reading from something normally blocks until there is something to read. This is not acceptable
in this case. The UDP socket you create will need to be set to non-blocking. Do this with 
the ```fcntl``` system call on an already opened DGRAM (UDP) socket. 

Here's the Beej comments on fcntl (https://beej.us/guide/bgnet/html/single/bgnet.html#fcntlman Beej)

Once the socket is set to non-blocking, attempting to read when there isn't anything there will return
immediately. It is up to you to tell the difference between an error and there simply no data being available.
Check ```errno``` for two values - ```EAGAIN``` and ```EWOULDBLOCK```. If ```errno``` is either of these
there wasn't really an error - just nothing to read.

# Some of the Berkeley sockets related functions you will use

You will use ```sendto``` and ```recvfrom``` to transmit and receive. These will both be done
over the same socket.

The ```socket``` function opens a socket. When you call this function you specify that the socket
is to speak UDP rather than another protocol. UDP sends and receives datagrams.

You will need the family of functions related to ```ntohl``` and the reverse ```htonl```. These
functions ensure a predictable ordering of bytes within an ```int``` (for example). Failure to use
these functions will lead to tears.

```fcntl``` is used to set the non-blocking mode on the socket. See above.

```gethostbyname``` will be used to turn a character / human readable server name into a number.


# Handy links

[A fairly complete cheat sheet](http://beej.us/guide/bgnet/html/single/bgnet.html "Beej")

# What to turn in

**Nothing** - don't turn in anything. Leave your code in exactly the place specified at the top
of this document. **DO NOT MODIFY ANY OF YOUR FILES IN THIS FOLDER AFTER THE DUE DATE**

