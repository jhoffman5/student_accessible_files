HEADERS =

default:	fleegman

main.o:		main.cpp $(HEADERS)
			g++ -O3 -std=c++11 -Wall -c main.cpp -o main.o

fleegman:	main.o
			g++ main.o -o fleegman -lpthread

clean:
			-rm -f main.o
			-rm -f fleegman