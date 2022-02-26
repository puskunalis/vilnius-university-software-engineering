#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define BACKLOG 10
#define BUFFER_LEN 1024

// Converts a string to uppercase
void upper(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        str[i] = toupper(str[i]);
    }
}

int main(int argc, char *argv[]) {
    // Get port number from command line
    if (argc < 2) {
        printf("Please supply a port number!\n");
        return 1;
    }
    char* port = argv[1];

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
    if (sockfd == -1) {
        perror("socket creation error");
        return 3;
    }

    // Clear address for use
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
        perror("setsockopt error");
        return 4;
    } 

    // Bind socket
    int bind_status = bind(sockfd, info->ai_addr, info->ai_addrlen);
    freeaddrinfo(info);
    if (bind_status == -1) {
        perror("bind error");
        return 5;
    }

    // Listen on socket
    int listen_status = listen(sockfd, BACKLOG);
    if (listen_status == -1) {
        perror("listen error");
        return 6;
    }
    printf("Listening on port %s, socket %d\n", port, sockfd);

    // Accept incoming connection
    struct sockaddr_storage client_addr;
    socklen_t addr_size = sizeof client_addr;
    int new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);
    if (new_fd == -1) {
        perror("connection accept error");
        return 7;
    }
    printf("Accepted incoming connection on socket %d\n", new_fd);

    // Receive message
    char *buf = (char*) malloc(BUFFER_LEN);
    int bytes_received = recv(new_fd, buf, BUFFER_LEN, 0);
    if (bytes_received == -1) {
        perror("message receive error");
        return 8;
    }
    printf("Received message: %s\n", buf);

    // Convert received message to uppercase
    upper(buf);

    // Send reply
    int bytes_sent = send(new_fd, buf, strlen(buf), 0);
    if (bytes_sent == -1) {
        perror("message send error");
        return 9;
    }
    printf("Sent reply: %s\n", buf);

    // Clean up (optional)
    free(buf);
    close(sockfd);
    close(new_fd);

    return 0;
}
