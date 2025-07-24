#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define BACKLOG 5 // connection request queue of 5
#define STRSZ 100
#define PORT 3000 
#define MAXCLIENTS 10

struct MessageStruct {
    int id;
    char msg[STRSZ];
};

typedef struct MessageStruct message;

/****************************/
// IMPORTANT: ERROR CHECK ALL SOCKET APIs
/****************************/

void *clientHandler(void *args) {
    int connfd = *((int *)args);

    // receive message from client
    message cmsg;
    int ret = recv(connfd, &cmsg, sizeof(cmsg), 0);
    if (ret == -1) {
        perror("recv error");
    }
    
    printf("Client %d: %s\n", cmsg.id, cmsg.msg);

    // close connection socket
    ret = close(connfd);
    if (ret == -1) {
        perror("close error");
    }

    return NULL;

}
int main(int argc, char *argv[]) {
    // create listening TCP socket
    int listen_fd;
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        perror("socket error");
    }

    // Forcefully attaching socket to the port
    // In your PA2-phase2, for each testcase, the server has to be stopped using Ctrl+C. You might get connection refused/bad binding the next time you run server
    // This occurs due to the abrupt interruption of the server in the previous run. To avoid this, use the following API. (samples/eg2)
    int opt = 1;
    if (setsockopt(listen_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // create sockaddr_in for server with listening port and address informatin
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind the listen_fd to servaddr
    int ret = bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (ret == -1) {
        perror("bind error");
    }

    // set the listening queue for server with backlog BACKLOG
    ret = listen(listen_fd, BACKLOG);
    if (ret == -1) {
        perror("listen error");
    }
    
    int conn_fd[MAXCLIENTS]; // connection sockets
    int conn_fd_iter = 0;

    pthread_t thds[MAXCLIENTS];
    while(1){
        if (conn_fd_iter >= MAXCLIENTS) {
            perror("conn_fd_iter index out of bounds");
            exit(EXIT_FAILURE);
        }
        // accept connection request from client and create new socket
        struct sockaddr_in clientaddr;
        socklen_t clientaddr_len = sizeof(clientaddr);
        conn_fd[conn_fd_iter] = accept(listen_fd, (struct sockaddr *) &clientaddr, &clientaddr_len);
        if (conn_fd[conn_fd_iter] == -1) {
            perror("accept error");
        }
        
        // create thread per connection that executes clientHandler
        ret = pthread_create(&thds[conn_fd_iter], NULL, clientHandler, &conn_fd[conn_fd_iter]);
        if (ret != 0) {
            perror("pthread_create error");
        }
        
        // detach the thread
        ret = pthread_detach(thds[conn_fd_iter]);
        if (ret != 0) {
            perror("pthread_detach error");
        }
        
        conn_fd_iter++;
    }

    // The following set of lines will never be executed.
    close(listen_fd);
    fprintf(stdout, "Server exiting...\n");
    return 0;

}