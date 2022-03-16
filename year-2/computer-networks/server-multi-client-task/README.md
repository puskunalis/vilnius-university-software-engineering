# Multi-client server task

## Usage:
1. Run server `S1` with `make run-server1` and server `S2` with `make run-server2`
1. Run some clients with `make run-client1` and `make run-client2`
1. Enter a message to send in format `@servername message`, for example `@S1 hello`
1. All clients on the given server will receive the message
