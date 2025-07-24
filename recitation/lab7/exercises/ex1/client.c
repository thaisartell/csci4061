#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STRSZ 100
#define PORT 3000

/****************************/
// IMPORTANT: ERROR CHECK ALL SOCKET APIs
/****************************/

int main(int argc, char *argv[]) {
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
    

    char msg[STRSZ] = "";
    while(1){
        fprintf(stdout, "Client: ");
        fscanf(stdin, "%[^\n]s", msg); // read input with space until a newline
        setbuf(stdin, NULL); // clear stdin buffer
        
        // send message to server
        ret = send(sockfd, msg, sizeof(msg), 0);
        if (ret == -1) {
            perror("send error");
        }
        // if message is END break out
        if (strcmp(msg, "END") == 0) {
            break;
        }
        // Receive message from server
        ret = recv(sockfd, msg, sizeof(msg), 0);
        if (ret == -1) {
            perror("receive error");
        }

        fprintf(stdout, "Server: %s\n", msg);
    }

    // close sockfd
    ret = close(sockfd);
    if (ret == -1) {
        perror("close error");
    }

    fprintf(stdout, "Client exiting...\n");

    return 0;
}