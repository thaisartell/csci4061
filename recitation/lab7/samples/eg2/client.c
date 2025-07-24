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
    int id = atoi(argv[1]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // create TCP socket
    if(sockfd == -1)
        perror("socket error");
    
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // server IP
    servaddr.sin_port = htons(PORT); //listening port 

    int ret = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if(ret == -1)
        perror("connection error");

    message cmsg;
    memset(&cmsg, 0, sizeof(cmsg));
    cmsg.id = id;
    fprintf(stdout, "Client: ");
    fscanf(stdin, "%[^\n]s", cmsg.msg); // read input with space until a newline
    setbuf(stdin, NULL); // clear stdin buffer

    ret = send(sockfd, &cmsg, sizeof(cmsg), 0);
    if(ret == -1)
        perror("client send error");

    close(sockfd);

    fprintf(stdout, "Client exiting...\n");

    return 0;
}