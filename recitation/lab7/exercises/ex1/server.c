#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BACKLOG 5 // connection request queue of 5
#define STRSZ 100
#define PORT 3000 

/****************************/
// IMPORTANT: ERROR CHECK ALL SOCKET APIs
/****************************/
int main(int argc, char *argv[]) {
    // create listening TCP socket
    int listen_fd;
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        perror("socket error");
    }

    // create sockaddr_in for server with listening port and address informatin
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind the listen_fd to servaddr
    int ret = bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if (ret == -1) {
        perror("bind error");
    }

    // set the listening queue for server
    ret = listen(listen_fd, BACKLOG);
    if (ret == -1) {
        perror("listen error");
    }

    // accept connection request from client and create new socket
    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    int conn_fd = accept(listen_fd, (struct sockaddr *) &clientaddr, &clientaddr_len);
    if (conn_fd == -1) {
        perror("accept error");
    }

    char msg[STRSZ] = "";
    while(1){
        // receive message from client
        ret = recv(conn_fd, msg, sizeof(msg), 0);
        if (ret == -1) {
            perror("recv error");
        }

        fprintf(stdout, "Client: %s\n", msg);
        
        // if message is END break out
        if (strcmp(msg, "END") == 0) {
            break;
        }
        fprintf(stdout, "Server: ");
        fscanf(stdin, "%[^\n]s", msg); // read input with space until a newline
        setbuf(stdin, NULL); // clear stdin buffer

        // Send message to client
        ret = send(conn_fd, msg, sizeof(msg), 0);
        if (ret == -1) {
            perror("send error");
        }
    }
    // close connection and listening socket
    ret = close(conn_fd);
    if (ret == -1) {
        perror("close connection error");
    }
    ret = close(listen_fd);
    if (ret == -1) {
        perror("close listen error");
    }
    
    fprintf(stdout, "Server exiting...\n");
    return 0;

}