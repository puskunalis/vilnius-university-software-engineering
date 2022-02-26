#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BACKLOG 10
#define BUFFER_LEN 1024

int main(int argc, char *argv[]) {
    // Get port number from command line
    if (argc < 2) {
        printf("Please supply a port number!\n");
        return 1;
    }
    char* port = argv[1];

    // Ask for text input
    printf("Enter a message to send: ");
    char* msg = (char*) malloc(BUFFER_LEN);
    fgets(msg, BUFFER_LEN, stdin);
    while (strlen(msg) <= 1) {
        printf("Enter a message to send: ");
        fgets(msg, BUFFER_LEN, stdin);
    }
    msg[strcspn(msg, "\n")] = 0;

    // Set hints
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Get address info
    struct addrinfo *info;
    int status = getaddrinfo(NULL, port, &hints, &info);
    if (status != 0) {
        printf("getaddrinfo error: %s\n", gai_strerror(status));
        return 2;
    }

    // Make socket
    int sockfd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (sockfd < 0) {
        perror("socket creation error");
        return 3;
    }

    // Connect to socket
    int connection = connect(sockfd, info->ai_addr, info->ai_addrlen);
    freeaddrinfo(info);
    if (connection == -1) {
        perror("connection error");
        return 4;
    }
    printf("Connected to socket %d\n", sockfd);

    // Send message
    int bytes_sent = send(sockfd, msg, strlen(msg), 0);
    if (bytes_sent == -1) {
        perror("message send error");
        return 5;
    }
    printf("Message sent!\n");

    // Receive reply
    char *buf = (char*) malloc(BUFFER_LEN);
    int bytes_received = recv(sockfd, buf, BUFFER_LEN, 0);
    if (bytes_received == -1) {
        perror("message receive error");
        return 6;
    }
    printf("Received reply: %s\n", buf);

    // Clean up (optional)
    free(buf);
    close(sockfd);
    
    return 0;
}
