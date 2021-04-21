CC=gcc

all: server client

server: 
	$(CC) -pthread server.c lib.c -o server.out 

client: 
	$(CC) -pthread client.c lib.c -o client.out 

clean :
	rm client.out server.out
