#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "sock.h"
#include "handler.h"

int serversocket = 0;

int prepare_socket(int portnum)
{
	struct sockaddr_in server;

	printf("#Bereite Socket vor...\n");
	if((serversocket=socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Fehler beim erstellen des serversockets.\n");
		return 1;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(portnum);
	server.sin_addr.s_addr = INADDR_ANY;

	if(bind(serversocket, (struct sockaddr *) &server, sizeof(struct sockaddr_in)) < 0)
	{
		return 1;
	}

	printf("#Socket bereit.\n");
	return 0;
}

void close_socket(void){
	close(serversocket);
	printf("#Socket geschlossen.\n");
}

int manage_connections(int anzverbindungen, int (*managerfunction) (FILE * datastream, char *information)){
	int newsock=0;
	int addrlen=0;
	struct sockaddr_in client_addr;
	struct sockaddr_in client;
	
	if(listen(serversocket, 5)<0){
		printf("#Fehler in listening().\n");
		return 1;
	}

	printf("#Lauschen\n");
	int i;
	for(i=0; i < anzverbindungen; i++){
		//Eine neue Verbindung!
		addrlen = sizeof( struct sockaddr_in );
		if((newsock = accept(serversocket,(struct sockaddr *) &client_addr, (socklen_t*) &addrlen)) < 0){  
	{  
			break;
		}

		printf("\n# Neue Verbindung erkannt:\n");

		FILE *datastream;

		if(!(datastream = fdopen(newsock, "a+"))){
			printf("#Fehler in fdopen().\n");
			close(newsock);
			return 1;
		}

		manager(datastream, inet_ntoa(client.sin_addr));
	    
	    fclose(datastream);
	    close(newsock);
	}
	return anzverbindungen;
}