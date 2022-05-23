#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>

void createMagicPacket(unsigned char packet[], unsigned int macAddress[]){
	int i;
	unsigned char mac[6];

	for(i = 0; i < 6; i++){
		packet[i] = 0xFF;
		mac[i] = macAddress[i];
	}

	for(i = 1; i <= 16; i++){
		memcpy(&packet[i * 6], &mac, 6 * sizeof(unsigned char));
	}
}

int main(int argc, const char* argv[]){
	int i = 0;
    	int broadcast = 1;
    	int socket_desc;

    	char broadcastAddress[16] = "";

    	struct sockaddr_in clientSide;
    	struct sockaddr_in serverSide;

    	unsigned char packet[102];
    	unsigned int mac[6];

	if(argc < 2){
		printf("No input\n");
		exit(EXIT_FAILURE);
	}

    	i = sscanf(argv[1],"%x:%x:%x:%x:%x:%x", &(mac[0]), &(mac[1]), &(mac[2]), &(mac[3]), &(mac[4]), &(mac[5]));
	if(i != 6){
		printf("Incorrect mac address.\n");
		exit(EXIT_FAILURE);
	}
	printf("\nPacket will sent to %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    	if(argc > 2){
		i = sscanf(argv[2],"%d.%d.%d.%d", &i, &i, &i, &i);
		if(i == 4){
			strcpy(broadcastAddress, argv[2]);
		}
	}

    	socket_desc = socket(AF_INET, SOCK_DGRAM, 0);
    	if(setsockopt(socket_desc, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast) == -1){
        	printf("The socket setup failed.\n");
        	exit(EXIT_FAILURE);
    	}

    	clientSide.sin_family = AF_INET;
    	clientSide.sin_addr.s_addr = INADDR_ANY;
    	clientSide.sin_port = 0;

    	bind(socket_desc, (struct sockaddr*) &clientSide, sizeof(clientSide));

    	serverSide.sin_family = AF_INET;
    	serverSide.sin_addr.s_addr = inet_addr(broadcastAddress);
    	serverSide.sin_port = htons(9);

        sendto(socket_desc, &packet, sizeof(unsigned char) * 102, 0, (struct sockaddr*) &serverSide, sizeof(serverSide));

	printf("\nSend packet to (mac address)");
	exit(EXIT_SUCCESS);
}
