#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT_FOR_REMOTE 38767
#define SOCKET_FILE     "chart_socket"

int main()
{
    char user[128];
    int m_choise = 0;
    struct sockaddr_un s_addr_un;
    struct sockaddr_in s_addr;
    struct sockaddr_in c_addr;
    int sock;
    int sock_un;
    socklen_t addr_len;
    int len;
    int ret;
    char buf[128];

    sock_un = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_un == -1) {
        perror("socketun");
        exit(1);
    }
    memset(&s_addr_un, 0, sizeof(struct sockaddr_un));
    s_addr_un.sun_family = AF_UNIX;
    strncpy(s_addr_un.sun_path, SOCKET_FILE, sizeof(s_addr_un.sun_path)+1);
    ret = connect(sock_un, (struct sockaddr *)&s_addr_un, sizeof(s_addr_un));
    if (ret == -1) {
        perror("connect");
        exit(2);
    }
    printf("connect recver success.\n");
    
    printf("\nHi!This is a program for you to send msg to your pals\n");
    printf("Please enter you name(which will be showed for your pals):");
    gets(user);
    printf("\n[%s],Welcome.\n",user);

    while (1) {
        printf("\nNow you can do these:\n");
        printf("\t(1) Scan available pals online.\n");
        printf("\t(2) List available pals online.\n");
        printf("\t(3) Chart with someone or in a group.\n");
        printf("\t(4) Quit.\n");
        printf("Your choise:");
        scanf("%d",&m_choise);
        switch (m_choise) {
            case 1:
                printf("\nScanning...\n");
                break;
            case 2:
                printf("\nAvailable pals:\n");
                break;
            case 3:
                printf("\nBegin chart with someone.\n");             
                break;
            case 4:
                printf("\nGoing to quit.bye\n");
                break;
            default:
                printf("\ninvaild option.choose again.\n");
        }
        if (m_choise == 4) {
            break;
        }
    }
    close(sock_un);
    return 0;
}
