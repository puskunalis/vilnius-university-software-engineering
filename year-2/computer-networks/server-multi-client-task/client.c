#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BACKLOG 10
#define BUFFER_LEN 1024

char* parse_args(int argc, char *argv[]) {
    // Get port number from command line
    if (argc < 2) {
        puts("Please supply a port number!");
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

char* receive_message(int sockfd, int *bytes_received) {
    char *buf = (char*) malloc(BUFFER_LEN);
    *bytes_received = recv(sockfd, buf, BUFFER_LEN, 0);
    if (*bytes_received == -1) {
        perror("message receive error");
        exit(6);
    }
    return buf;
}

void *message_receiver(void *ptr) {
    int bytes_received;

    while (1) {
        char *msg = receive_message(*(int*) ptr, &bytes_received);
        if (bytes_received == 0) {
            free(msg);
            return NULL;
        }
        printf("Received message: %s\n", msg);
        free(msg);
    }
}

int main(int argc, char *argv[]) {
    char* port = parse_args(argc, argv);

    struct addrinfo *info = load_addr_info(port);

    int sockfd = make_socket(info);

    connect_to_socket(sockfd, info);
    printf("Connected to socket %d\n", sockfd);

    pthread_t receiver_thread;
    pthread_create(&receiver_thread, NULL, message_receiver, (void*)&sockfd);

    while (1) {
        char* msg = get_input();
        send_message(sockfd, msg);
        free(msg);
        puts("Message sent!");
    }

    // Clean up (optional)
    freeaddrinfo(info);
    close(sockfd);
    
    return 0;
}
