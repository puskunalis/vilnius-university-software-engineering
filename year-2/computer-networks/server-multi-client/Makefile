.DEFAULT_GOAL := default

.PHONY: default
default: run-server

.PHONY: run-client
run-client: client
	./client 1000

.PHONY: run-server
run-server: server
	./server 1000

.PHONY: client
client:
	gcc -o client client.c

.PHONY: server
server:
	gcc -o server server.c
