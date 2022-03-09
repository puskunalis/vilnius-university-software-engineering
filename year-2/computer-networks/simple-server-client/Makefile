.DEFAULT_GOAL := default

.PHONY: default
default: client server
	(./server 1000 > /dev/null) &
	(./client 1000)
	rm client server

.PHONY: client
client:
	gcc -o client client.c

.PHONY: server
server:
	gcc -o server server.c
