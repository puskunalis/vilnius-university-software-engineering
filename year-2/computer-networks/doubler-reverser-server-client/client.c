#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BACKLOG 10
#define BUFFER_LEN 1024

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

void bind_socket(int sockfd, struct addrinfo *info) {
    // Clear address for use
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
        perror("setsockopt error");
        exit(8);
    } 

    // Bind socket
    int bind_status = bind(sockfd, info->ai_addr, info->ai_addrlen);
    if (bind_status == -1) {
        perror("bind error");
        exit(9);
    }
}

void listen_on_socket(int sockfd) {
    int listen_status = listen(sockfd, BACKLOG);
    if (listen_status == -1) {
        perror("listen error");
        exit(10);
    }
}

int main(int argc, char *argv[]) {
    // Get port number from command line
    if (argc < 3) {
        printf("Please supply two port numbers!\n");
        exit(1);
    }
    char* send_port = argv[1];
    char* recv_port = argv[2];

    char* msg = get_input();

    struct addrinfo *info = load_addr_info(send_port);
    
    int sockfd = make_socket(info);

    connect_to_socket(sockfd, info);
    printf("Connected to socket %d\n", sockfd);

    send_message(sockfd, msg);
    printf("Message sent: %s\n", msg);

    struct addrinfo *info_recv = load_addr_info(recv_port);
    
    int sockfd_recv = make_socket(info_recv);

    bind_socket(sockfd_recv, info_recv);

    listen_on_socket(sockfd_recv);
    printf("Listening on port %s, socket %d\n", recv_port, sockfd_recv);

    int newfd = accept_connection(sockfd_recv);
    printf("Accepted incoming connection on socket %d\n", newfd);

    char *msg_recv = receive_message(newfd);
    printf("Received message: %s\n", msg_recv);

    // Clean up (optional)
    freeaddrinfo(info);
    freeaddrinfo(info_recv);
    close(sockfd);
    close(sockfd_recv);
    close(newfd);
    
    return 0;
}
