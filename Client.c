#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define port 5000

int main(){
    int sock = 0;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};
    char *message = "Victoria" ;

    if((sock = socket(AF_INET,SOCK_STREAM,0))<0){
        perror("socket creation error");
        return -1;
    }
    printf("Socket Created Successfully. \n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr)<=0){
        perror("invalid address or address not supported");
        return -1;
    }

    if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        perror("connection failed");
        return -1;
    }
    printf("connected to the Server.\n");

    send(sock, message, strlen(message), 0);
    printf("message sent to server: %s\n", message);

    int valread = read(sock, buffer, sizeof(buffer));
    printf("Message Recived from server: %s\n", buffer);
    
    close(sock);
    return 0;

}