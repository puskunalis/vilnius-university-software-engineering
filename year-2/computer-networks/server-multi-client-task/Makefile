.DEFAULT_GOAL := default

.PHONY: default
default: run-server1

.PHONY: run-client1
run-client1: client
	./client 10000

.PHONY: run-client2
run-client2: client
	./client 10001

.PHONY: run-server1
run-server1: server
	./server S1 10000 10001

.PHONY: run-server2
run-server2: server
	./server S2 10001 10000

.PHONY: client
client:
	gcc -o client client.c

.PHONY: server
server:
	gcc -o server server.c
