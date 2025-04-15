#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>

int main(){
    int sockfd = -1;
    struct sockaddr_in serv_addr;
    char recv_buffer[1024];
    memset(recv_buffer, 0, sizeof(recv_buffer));
    memset(&serv_addr, 0, sizeof(serv_addr));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(5000);

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0){
        printf("Connected to server\n");
        read(sockfd, recv_buffer, sizeof(recv_buffer));
        printf("Received: %s\n", recv_buffer);

    } else {
        printf("Connection failed: %s\n", strerror(errno));
    }
    close(sockfd);

}