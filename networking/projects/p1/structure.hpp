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

#include <stdint.h>

struct ClientDatagram
{
	uint32_t sequence_number;
	uint16_t  payload_length;
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
	uint32_t  sequence_number;
	uint16_t  datagram_length;
};

