CFLAGS	= -Wall -std=c++11 -g
CC		= g++
COBJS	= client.o
SOBJS	= server.o

client		: 	$(COBJS)
			$(CC) -o $@ $(COBJS)

client.o	:	client.cpp 
			$(CC) $(CFLAGS) -c client.cpp

server		:	server.o
			$(CC) -o $@ server.o
			
server.o	:	server.cpp
			$(CC) $(CFLAGS) -c server.cpp


clean		:
			rm -f *.o client server

