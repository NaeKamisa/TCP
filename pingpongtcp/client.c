#include <stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

char buf[BUFSIZ];
int server_fd;
int client_fd;
void send_msg(){
    char envoie[BUFSIZ];
    while (1)
    {
        memset(envoie,0,BUFSIZ);
        fgets(envoie,BUFSIZ,stdin);
        send(client_fd,envoie,BUFSIZ,0);
    }
    
}

void receive_msg(){
    char receive[BUFSIZ];
    while (1)
    {
        memset(receive,0,BUFSIZ);
        recv(client_fd,receive,BUFSIZ,0);
        printf("%s\n",receive);
    }
    
}



int main (){
    pthread_t thread_receive;
    pthread_t thread_send;

    server_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket()");
    client_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket()");


    if(server_fd == -1) return  EXIT_FAILURE;

    struct sockaddr_in server_addr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(3602)
    };
    struct sockaddr_in server_client = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(3605)
    };

    int error = bind(client_fd,(struct sockaddr*)&server_client,sizeof server_addr);perror("bind()");
    if(error == -1) return EXIT_FAILURE;

    connect(client_fd,(struct sockaddr*)&server_addr,sizeof server_addr);perror("connect()");
    if(error == -1) return EXIT_FAILURE;

    
    pthread_create()
while (1)
{   
    
    
}


    close(client_fd);

    return 0;
}