#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{

    int listenfd = -1;
    int connfd = -1;
    struct sockaddr_in serv_addr;
    char send_buffer[1024];

    time_t ticks;

    memset(send_buffer, 0, sizeof(send_buffer));
    memset(&serv_addr, 0, sizeof(serv_addr));

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);

    while (1)
    {
        connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);
        ticks = time(NULL);
        write(connfd, ctime(&ticks), sizeof(send_buffer));
        close(connfd);
    }
    close(listenfd);
    return 0;
}