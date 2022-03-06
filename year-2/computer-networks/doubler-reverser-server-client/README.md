# One server - one client task

## Usage:
1. Compile the reverser, doubler and client
1. Run any number of reversers and doublers with a receiving and a sending port, for example: `./reverser 1000 1001` and `./doubler 1001 1002`
1. Run the client with the sending and receiving port, for example: `./client 1000 1002`
1. Enter the message to send
1. The message will be routed and returned back to the client
