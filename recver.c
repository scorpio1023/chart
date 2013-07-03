#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define SOCKET_FILE     "chart_socket"

int main()
{
    int s_sockfd, c_sockfd;
    int s_len, c_len;
    struct sockaddr_un s_addr, c_addr;
    int i, byte;

    unlink(SOCKET_FILE);
    s_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (s_sockfd == -1) {
        perror("socket");
        exit(1);
    }
    
    s_addr.sun_family = AF_UNIX;
    strncpy(s_addr.sun_path, SOCKET_FILE, sizeof(s_addr.sun_path)+1);
    s_len = sizeof(s_addr);
    if(bind(s_sockfd, (struct sockaddr *)&s_addr, s_len) == -1) {
        perror("bind");
        exit(2);
    }
    c_len = sizeof(c_addr);
    
    listen(s_sockfd, 5);
    printf("Waiting for sender to connect\n");
    c_sockfd = accept(s_sockfd, (struct sockaddr *)&c_addr, (socklen_t *)&c_len);
    if (c_sockfd == -1) {
        perror("accept");
        exit(3);
    }
    printf("sender connected.\n");
    close(c_sockfd);
    unlink(SOCKET_FILE);
    return 0;
}
