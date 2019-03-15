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
    int i;
    int cont;
	int sockfd, ret;
    int CC = 10; ///Cantidad de clientes que se va a atender al mismo tiempo
	 struct sockaddr_in serverAddr;

	int newSocket[1000];
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	//char buffer[1024];
    
	pid_t childpid;
void *clien(void *arg);
int main(){
    pthread_t  h1;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, CC) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}


	while(1){
        //printf("cero \n");
		newSocket[i] = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
        i=i+1;
        //printf("uno %d\n",newSocket);
		if(newSocket < 0){
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
        ///Se  activa la funcion clien cuando se necesita, en este caso dentro de while(1)
        //printf("dos \n");

        if(cont != 0){
          pthread_exit(&h1);
        }
        pthread_create(&h1, NULL , clien , NULL);
        //pthread_create(&h2,NULL,Enviar)
        //printf("tres \n");
	}
    close(newSocket);



	return 0;
}
void *clien(void *arg){
		int a=i-1;
        int j=0;
        printf("%d \n",a);
        char buffer[1024];
			while(1){
                    //for(a=0;a<i;a++){    
                        recv(newSocket[a], buffer, 1024, 0);
                        if(strcmp(buffer,":EXIT")==0){
                            printf("[-]Se ha desconectado un cliente.\n");
                        }else{
                            printf("Client: %s \n", buffer); 
                        }
                        for(j=0;j<i;j++){
                          send(newSocket[j], buffer, strlen(buffer), 0);  
                        }
                        j=0;
                        //printf("%d \n", newSocket[a]);  
                        bzero(buffer, sizeof(buffer));
                        
                    //}
			}
		
}