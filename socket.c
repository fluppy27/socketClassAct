#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#define port 5000

typedef struct{
    char* desc;
    float temp;
    float humid;
} City;

City* init_City(char* desc, float temp, float humid){
    City* city = malloc(sizeof(City));
    city->desc = desc;
    city->temp = temp;
    city->humid = humid;
    return city;
} 

int main(){
    int server_fd, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer [1024] = {0};
    char *response = "hello from server";

    City* Victoria = init_City("nice and warm today", 19, 62);

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("Socket creation 2");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully. \n");
 //printf("1 \n");
    server_addr.sin_family = AF_INET;
    //printf("1 \n");
    server_addr.sin_addr.s_addr = INADDR_ANY;
    //printf("2 \n");
    server_addr.sin_port = htons(port);
    //printf("3 \n");

    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        perror("bind failed");
        close(EXIT_FAILURE);
        exit(EXIT_FAILURE);
    }
    printf("Bind successful. \n");
    while(1){
        if(listen(server_fd, 3) > 0){
            perror("Listen Failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        printf("server is listening on port %d... \n",port);
        
        

        if((new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) <0 ){
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        printf("client connected\n");

        int valread = read(new_socket, buffer, sizeof(buffer));
        printf("message recived from client: %s \n", buffer);

        if(strcmp(buffer,"Victoria") == 0){
            response = "the weather is cloudy with a chance of rain, its 7 degrees and 57%% humidity \n";
            send(new_socket, response, strlen(response), 0);
            printf("resposne sent to client: %s \n", response);
        }
        else if(strcmp(buffer,"Vancouver") == 0){
            response = "the weather is Sunny and clear sky, its 12 degrees and 70%% humidity \n";
            send(new_socket, response, strlen(response), 0);
            printf("resposne sent to client: %s \n", response);
        }   
        else{
            response = "non valid City";
            send(new_socket, response, strlen(response), 0);
            printf("resposne sent to client: %s \n", response);
        }
    }
    close(new_socket);
    close(server_fd);
    return 0;
}