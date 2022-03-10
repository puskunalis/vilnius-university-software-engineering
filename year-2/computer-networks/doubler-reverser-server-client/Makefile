.DEFAULT_GOAL := default

ip = ::1

.PHONY: default
default: client reverser doubler
	(./reverser $(ip) 10000 10001 > /dev/null) &
	(./doubler $(ip) 10001 10002 > /dev/null) &
	(./reverser $(ip) 10002 10003 > /dev/null) &
	./client $(ip) 10000 10003
	rm client reverser doubler

.PHONY: client
client:
	gcc -o client client.c

.PHONY: reverser
reverser:
	gcc -o reverser reverser.c

.PHONY: doubler
doubler:
	gcc -o doubler doubler.c
