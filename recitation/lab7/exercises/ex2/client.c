#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define STRSZ 100
#define PORT 3000

struct MessageStruct {
    int id;
    char msg[STRSZ];
};

typedef struct MessageStruct message;

/****************************/
// IMPORTANT: ERROR CHECK ALL SOCKET APIs
/****************************/

int main(int argc, char *argv[]) {
    // pass one argument to client
    if(argc != 2){
        printf("ERROR: Usage: ./client <clientid>");
        exit(EXIT_FAILURE);
    }
    int id = atoi(argv[1]); // client id

    // create TCP socket
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket error");
    }

    // create sockaddr with server information
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // connect to server using sockfd
    int ret = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if (ret == -1) {
        perror("connection error");
    }

    message cmsg;
    memset(&cmsg, 0, sizeof(cmsg));
    cmsg.id = id;
    fprintf(stdout, "Client: ");
    fscanf(stdin, "%[^\n]s", cmsg.msg); // read input with space until a newline
    setbuf(stdin, NULL); // clear stdin buffer

    // send message to server
    ret = send(sockfd, &cmsg, sizeof(cmsg), 0);
    if (ret == -1) {
        perror("send error");
    }

    // close sockfd
    ret = close(sockfd);
    if (ret == -1) {
        perror("close error");
    }

    fprintf(stdout, "Client exiting...\n");

    return 0;
}