#include <stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>


int main (){
 
    char response[BUFSIZ];
    int server_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket()");
    if(server_fd == -1) return  EXIT_FAILURE;

    struct sockaddr_in server_addr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(3602)
    };

    int error = bind(server_fd,(struct sockaddr*)&server_addr,sizeof server_addr);
    if(error == -1) return EXIT_FAILURE;

    listen(server_fd,BUFSIZ);perror("listen()");
    if(error == -1) return EXIT_FAILURE;
    
struct sockaddr client_addr;
    socklen_t len;
    int client_fd = accept(server_fd,&client_addr,&len);perror("accept()"); 
while (1){

    memset(response,0,BUFSIZ);

    recv(client_fd,response,BUFSIZ,0);
    printf("%s\n",response);
    memset(response,0,BUFSIZ);
    fgets(response,BUFSIZ,stdin);
    send(client_fd,response,5,0);perror("send()");

    memset(response,0,BUFSIZ);
}

    close(client_fd);
    return 0;
}



    