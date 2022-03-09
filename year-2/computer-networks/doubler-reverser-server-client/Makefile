.DEFAULT_GOAL := default

.PHONY: default
default: client reverser doubler
	(./reverser 1000 1001 > /dev/null) &
	(./doubler 1001 1002 > /dev/null) &
	(./reverser 1002 1003 > /dev/null) &
	./client 1000 1003
	rm client reverser doubler

client: reverser doubler
	gcc -o client client.c

reverser:
	gcc -o reverser reverser.c

doubler:
	gcc -o doubler doubler.c
