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

char* parse_args(int argc, char *argv[]) {
    // Get port number from command line
    if (argc < 2) {
        printf("Please supply a port number!\n");
        exit(1);
    }

    return argv[1];
}

struct addrinfo* load_addr_info(char *port) {
    // Set hints
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Get address info
    struct addrinfo *info;
    int status = getaddrinfo(NULL, port, &hints, &info);
    if (status != 0) {
        printf("getaddrinfo error: %s\n", gai_strerror(status));
        exit(2);
    }

    return info;
}

int make_socket(struct addrinfo *info) {
    int sockfd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (sockfd < 0) {
        perror("socket creation error");
        exit(3);
    }

    return sockfd;
}

void bind_socket(int sockfd, struct addrinfo *info) {
    // Clear address for use
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
        perror("setsockopt error");
        exit(4);
    } 

    // Bind socket
    int bind_status = bind(sockfd, info->ai_addr, info->ai_addrlen);
    if (bind_status == -1) {
        perror("bind error");
        exit(5);
    }
}

void listen_on_socket(int sockfd) {
    int listen_status = listen(sockfd, BACKLOG);
    if (listen_status == -1) {
        perror("listen error");
        exit(6);
    }
}

int accept_connection(int sockfd) {
    struct sockaddr_storage client_addr;
    socklen_t addr_size = sizeof client_addr;
    int newfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);
    if (newfd == -1) {
        perror("connection accept error");
        exit(7);
    }
    return newfd;
}

char* receive_message(int sockfd) {
    char *buf = (char*) malloc(BUFFER_LEN);
    int bytes_received = recv(sockfd, buf, BUFFER_LEN, 0);
    if (bytes_received == -1) {
        perror("message receive error");
        exit(8);
    }
    return buf;
}

void send_message(int sockfd, char *reply) {
    int bytes_sent = send(sockfd, reply, strlen(reply), 0);
    if (bytes_sent == -1) {
        perror("message send error");
        exit(9);
    }
}

int main(int argc, char *argv[]) {
    char* port = parse_args(argc, argv);

    struct addrinfo *info = load_addr_info(port);
    
    int sockfd = make_socket(info);

    bind_socket(sockfd, info);

    listen_on_socket(sockfd);
    printf("Listening on port %s, socket %d\n", port, sockfd);

    int newfd = accept_connection(sockfd);
    printf("Accepted incoming connection on socket %d\n", newfd);

    char *msg = receive_message(newfd);
    printf("Received message: %s\n", msg);

    // Convert received message to uppercase
    upper(msg);

    send_message(newfd, msg);
    printf("Sent reply: %s\n", msg);

    // Clean up (optional)
    freeaddrinfo(info);
    free(msg);
    close(sockfd);
    close(newfd);

    return 0;
}
