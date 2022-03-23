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
#define MAX_CLIENTS 32

typedef struct Client {
    int sockfd;
    char *name;
} Client;

char** parse_args(int argc, char *argv[]) {
    if (argc < 4) {
        puts("Please supply a server name, receiving port and sending port!");
        exit(1);
    }
    return argv;
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

char* receive_message(int sockfd, int *bytes_received) {
    char *buf = (char*) calloc(BUFFER_LEN, sizeof(char));
    *bytes_received = recv(sockfd, buf, BUFFER_LEN, 0);
    if (*bytes_received == -1) {
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

int is_prefix(char *prefix, char *str) {
    return strncmp(prefix, str, strlen(prefix)) == 0;
}

int connect_to_socket(int sockfd, struct addrinfo *info) {
    return connect(sockfd, info->ai_addr, info->ai_addrlen);
}

int connect_to_server(char* port) {
    struct addrinfo *info = load_addr_info(port);
    int sockfd;

    while (1) {
        sockfd = make_socket(info);
        int connection = connect_to_socket(sockfd, info);
        if (connection == -1) {
            puts("Failed to connect to another server, retrying in 2 seconds...");
            close(sockfd);
            sleep(2);
        } else {
            break;
        }
    }

    printf("Connected to another server on socket %d\n", sockfd);
    return sockfd;
}

int main(int argc, char *argv[]) {
    char** args = parse_args(argc, argv);
    char* server_name = args[1];
    char* recv_port = args[2];
    char* send_port = args[3];

    Client** clients = (Client**) calloc(MAX_CLIENTS, sizeof(Client*));
    int clients_num = 0;

    struct addrinfo *info = load_addr_info(recv_port);
    
    int sockfd = make_socket(info);

    bind_socket(sockfd, info);
    freeaddrinfo(info);

    listen_on_socket(sockfd);
    printf("Listening on port %s, socket %d\n", recv_port, sockfd);

    fd_set master;
    FD_ZERO(&master);
    FD_SET(sockfd, &master);

    fd_set read_fds;
    FD_ZERO(&read_fds);

    int fdmax = sockfd;

    int serversockfd = connect_to_server(send_port);

    int newserversockfd = accept_connection(sockfd);
    FD_SET(newserversockfd, &master);
    printf("Connection accepted from another server on socket %d\n", newserversockfd);

    while (1) {
        read_fds = master;

        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(10);
        }

        for (int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == sockfd) {
                    int newfd = accept_connection(sockfd);
                    printf("Connection accepted on socket %d\n", newfd);
                    FD_SET(newfd, &master);
                    if (newfd > fdmax) {
                        fdmax = newfd;
                    }
                    while (1) {
                        send_message(newfd, "ATSIUSKVARDA\n");
                        int bytes_received;
                        char* msg = receive_message(newfd, &bytes_received);
                        msg[strcspn(msg, "\r")] = 0;
                        msg[strcspn(msg, "\n")] = 0;
                        int name_exists = 0;
                        for (int j = 0; j < clients_num; j++) {
                            if (strcmp(msg, clients[j]->name) == 0) {
                                name_exists = 1;
                                break;
                            }
                        }
                        if (name_exists) {
                            continue;
                        }
                        Client* client = (Client*) malloc(sizeof(Client));
                        client->name = msg;
                        client->sockfd = newfd;
                        clients[clients_num] = client;
                        clients_num++;
                        send_message(newfd, "VARDASOK\n");
                        break;
                    }
                } else {
                    int bytes_received;
                    char* msg = receive_message(i, &bytes_received);
                    if (bytes_received == 0) {
                        printf("Socket %d hung up\n", i);
                        close(i);
                        FD_CLR(i, &master);
                    } else {
                        printf("Received message from socket %d of length %d: %s\n", i, bytes_received, msg);
                        char *prefix = (char*) calloc(BUFFER_LEN+1, sizeof(char));
                        prefix[0] = '@';
                        strcpy(prefix+1, server_name);
                        if (is_prefix(prefix, msg)) {
                            msg = msg + 2 + strlen(server_name);
                        } else if (msg[0] == '@') {
                            send_message(serversockfd, msg);
                            free(msg);
                            continue;
                        }
                        char *name;
                        for (int j = 0; j < clients_num; j++) {
                            if (i == clients[j]->sockfd) {
                                name = clients[j]->name;
                            }
                        }
                        char *namedMsg = (char*) calloc(BUFFER_LEN*2, sizeof(char));
                        strcpy(namedMsg, "PRANESIMAS");
                        strcpy(namedMsg+10, name);
                        int len = strlen(namedMsg);
                        namedMsg[len] = ':';
                        namedMsg[len+1] = ' ';
                        strcpy(namedMsg+len+2, msg);
                        for (int j = 0; j <= fdmax; j++) {
                            if (FD_ISSET(j, &master)) {
                                if (j != sockfd) {
                                    send_message(j, namedMsg);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
