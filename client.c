#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define CLIENT_PORT 3002
int main(){

    int client_fd;
    int server_fd;

    client_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket()");
    server_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket()");
    
    struct sockaddr_in addrclient ={
        .sin_addr.s_addr = INADDR_ANY,  
        .sin_family = AF_INET,
        .sin_port = htons(CLIENT_PORT)
    };
    bind(client_fd,(struct sockaddr*)&addrclient,sizeof(addrclient));perror("bind()");
    struct sockaddr_in addr = {
        .sin_port = htons(3001),
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
    };
    socklen_t len;
    connect(client_fd,(struct sockaddr*)&addr,sizeof addr);perror("connect()");

    char buf[BUFSIZ];memset(buf,0,BUFSIZ);
    fgets(buf,BUFSIZ,stdin);
    send(client_fd,buf,BUFSIZ,0);perror("send()");
    memset(buf,0,BUFSIZ);
    recv(client_fd,buf,BUFSIZ,0);perror("recv()");
    printf("%s\n",buf);


    close(client_fd);
    return 0;
}