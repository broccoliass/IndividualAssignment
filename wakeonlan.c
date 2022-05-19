#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, const char* argv[]){
    int i = 0;
	int broadcast = 1;
    int socket_desc;

    char broadcastAddress[16] = "";

    struct sockaddr_in clientSide;
    struct sockaddr_in serverSide;

	if(argc < 2){
		printf("No input\n");
		exit(EXIT_FAILURE);
	}

    socket_desc = socket(AF_INET, SOCK_DGRAM, 0);
  

    clientSide.sin_family = AF_INET;
    clientSide.sin_addr.s_addr = INADDR_ANY;
    clientSide.sin_port = 0;

    bind(socket_desc, (struct sockaddr*) &clientSide, sizeof(clientSide));

    serverSide.sin_family = AF_INET;
    serverSide.sin_addr.s_addr = inet_addr(broadcastAddress);
    serverSide.sin_port = htons(9);

	printf("\nWaking up (mac address)");
	exit(EXIT_SUCCESS);
}
