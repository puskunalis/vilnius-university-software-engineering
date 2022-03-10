.DEFAULT_GOAL := default

.PHONY: default
default: run-server

.PHONY: run-client
run-client: client
	./client 10000

.PHONY: run-server
run-server: server
	./server 10000

.PHONY: client
client:
	gcc -o client client.c

.PHONY: server
server:
	gcc -o server server.c
