#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define SERVER_PORT 3001

    int clients[BUFSIZ];
    int nb_clients = 0;
    int server_fd;
    int client_fd;

void* accept_thread(){
    while (1)
    {
        struct sockaddr client_addr;
        socklen_t len;
        int client_fd = accept(server_fd,&client_addr,&len); perror("accept()");
        clients[nb_clients] = client_fd;
        nb_clients++;
    }
}


int main(){



    server_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket()");
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(SERVER_PORT)
    };

    bind(server_fd,(struct sckaddr*)&addr,sizeof(addr));perror("bind()");

    listen(server_fd,BUFSIZ);perror("listen()");
    printf("Server listen to 127.0.0.1:%d\n",SERVER_PORT);

    pthread_t thread;
    pthread_create(&thread,NULL,accept_thread,NULL);
    printf("Thread starts...");

            char buf[BUFSIZ]; memset(buf,0,BUFSIZ);
    while(1){
        for (int i = 0; i < nb_clients; i++)
        {
            memset(buf,0,BUFSIZ);
            recv(clients[i],buf,BUFSIZ,0);perror("recv()");
            printf("%d\n",buf);
            for (int j = 0; j < nb_clients; j++)
            {
                send(clients[j],buf,strlen(buf),0);
            }

            close(clients[i]);perror("close");
        }
    }

     if(strlen(buf) > 0){
            printf("> %s\n",buf);
            memset(buf,0,BUFSIZ);
            char html[BUFSIZ];memset(html,0,BUFSIZ);
            FILE* fd_html = fopen("index.html","r+");
            fread(html,sizeof(char),BUFSIZ,fd_html);
            
            char response[BUFSIZ];memset(response,0,BUFSIZ);
            
            sprintf(response,"HTTP/1.1 200 OK\n\n%s",html);
            send(client_fd,response,strlen(response),0);
    printf("Server shutsdown...\n");
}