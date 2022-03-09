#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BACKLOG 10
#define BUFFER_LEN 1024
#define SOCKETS 5

char* parse_args(int argc, char *argv[]) {
    // Get port number from command line
    if (argc < 2) {
        printf("Please supply a port number!\n");
        exit(1);
    }

    return argv[1];
}

char* get_input() {
    // Ask for text input
    printf("Enter a message to send: ");
    char* msg = (char*) malloc(BUFFER_LEN);
    fgets(msg, BUFFER_LEN, stdin);
    while (strlen(msg) <= 1) {
        printf("Enter a message to send: ");
        fgets(msg, BUFFER_LEN, stdin);
    }
    msg[strcspn(msg, "\n")] = 0;
    return msg;
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
    // Make socket
    int sockfd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (sockfd < 0) {
        perror("socket creation error");
        exit(3);
    }

    return sockfd;
}

void connect_to_socket(int sockfd, struct addrinfo *info) {
    int connection = connect(sockfd, info->ai_addr, info->ai_addrlen);
    if (connection == -1) {
        perror("connection error");
        exit(4);
    }
}

void send_message(int sockfd, char *reply) {
    int bytes_sent = send(sockfd, reply, strlen(reply), 0);
    if (bytes_sent == -1) {
        perror("message send error");
        exit(5);
    }
}

char* receive_message(int sockfd) {
    char *buf = (char*) malloc(BUFFER_LEN);
    int bytes_received = recv(sockfd, buf, BUFFER_LEN, 0);
    if (bytes_received == -1) {
        perror("message receive error");
        exit(6);
    }
    return buf;
}

int main(int argc, char *argv[]) {
    char* port = parse_args(argc, argv);

    char* msg = get_input();

    struct addrinfo *info = load_addr_info(port);

    int sockfds[SOCKETS];

    for (int i = 0; i < SOCKETS; i++) {
        sockfds[i] = make_socket(info);

        connect_to_socket(sockfds[i], info);
        printf("Connected to socket %d\n", sockfds[i]);
    }

    for (int i = 0; i < SOCKETS; i++) {
        send_message(sockfds[i], msg);
        printf("Message sent!\n");

        char *rep = receive_message(sockfds[i]);
        printf("Received reply: %s\n", rep);
        free(rep);
    }

    // Clean up (optional)
    freeaddrinfo(info);
    for (int i = 0; i < SOCKETS; i++) {
        close(sockfds[i]);
    }
    
    return 0;
}
