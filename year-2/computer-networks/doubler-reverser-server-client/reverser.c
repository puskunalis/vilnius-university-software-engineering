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

// Reverses a string
void strrev(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
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
        exit(1);
    }

    return info;
}

int make_socket(struct addrinfo *info) {
    int sockfd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (sockfd < 0) {
        perror("socket creation error");
        exit(2);
    }

    return sockfd;
}

void bind_socket(int sockfd, struct addrinfo *info) {
    // Clear address for use
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
        perror("setsockopt error");
        exit(3);
    } 

    // Bind socket
    int bind_status = bind(sockfd, info->ai_addr, info->ai_addrlen);
    if (bind_status == -1) {
        perror("bind error");
        exit(4);
    }
}

void listen_on_socket(int sockfd) {
    int listen_status = listen(sockfd, BACKLOG);
    if (listen_status == -1) {
        perror("listen error");
        exit(5);
    }
}

int accept_connection(int sockfd) {
    struct sockaddr_storage client_addr;
    socklen_t addr_size = sizeof client_addr;
    int newfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);
    if (newfd == -1) {
        perror("connection accept error");
        exit(6);
    }
    return newfd;
}

char* receive_message(int sockfd) {
    char *buf = (char*) malloc(BUFFER_LEN);
    int bytes_received = recv(sockfd, buf, BUFFER_LEN, 0);
    if (bytes_received == -1) {
        perror("message receive error");
        exit(7);
    }
    return buf;
}

void send_message(int sockfd, char *reply) {
    int bytes_sent = send(sockfd, reply, strlen(reply), 0);
    if (bytes_sent == -1) {
        perror("message send error");
        exit(8);
    }
}

void connect_to_socket(int sockfd, struct addrinfo *info) {
    int connection = connect(sockfd, info->ai_addr, info->ai_addrlen);
    if (connection == -1) {
        perror("connection error");
        exit(9);
    }
}

int main(int argc, char *argv[]) {
    // Get port number from command line
    if (argc < 3) {
        printf("Please supply two port numbers!\n");
        exit(1);
    }
    char* recv_port = argv[1];
    char* send_port = argv[2];

    struct addrinfo *info = load_addr_info(recv_port);
    
    int sockfd = make_socket(info);

    bind_socket(sockfd, info);

    listen_on_socket(sockfd);
    printf("Listening on port %s, socket %d\n", recv_port, sockfd);

    int newfd = accept_connection(sockfd);
    printf("Accepted incoming connection on socket %d\n", newfd);

    char *msg = receive_message(newfd);
    printf("Received message: %s\n", msg);

    // Reverse message
    strrev(msg);

    struct addrinfo *info_recv = load_addr_info(send_port);
    
    int sockfd_send = make_socket(info_recv);

    connect_to_socket(sockfd_send, info_recv);
    printf("Connected to socket %d\n", sockfd_send);

    send_message(sockfd_send, msg);
    printf("Message sent: %s\n", msg);

    // Clean up (optional)
    freeaddrinfo(info);
    freeaddrinfo(info_recv);
    free(msg);
    close(sockfd);
    close(sockfd_send);
    close(newfd);

    return 0;
}
