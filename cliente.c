#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 4444 /// Puerto que se va a usar
    
	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];
    void *reciv(void *arg);
int main(){
    pthread_t  h1;
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

    pthread_create(&h1, NULL , reciv , NULL);
	while(1){
        //fflush(stdin);
		gets(buffer);
        
        if(strcmp(buffer,":EXIT")==0){
            close(clientSocket);
            printf("[-]Se ha desconectado del servidor.\n");
            exit(1);
        }
        printf("\n");
		send(clientSocket, buffer, strlen(buffer), 0);
        bzero(buffer, sizeof(buffer));    
	}

	return 0;
}


void *reciv(void *arg){
    while(1){
        if(recv(clientSocket, buffer, 1024, 0) < 0){
                printf("[-]Error in receiving data.\n");
            }else{
                printf("Server: %s\n", buffer);
            }	
    bzero(buffer, sizeof(buffer));
    }
}





