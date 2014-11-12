#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "handler.h"

int manager(FILE * datastream, char *information){
	char *InvReq = "HTTP/1.1 501 No implemented\r\n";
  	char *WrongVersion = "HTTP/1.1 505 HTTP Version Not Supported\r\n";
    char *NoHost = "HTTP/1.1 400 Bad Request\r\n";

    char header[] = "Content-Type: text/plain\r\n\n";
    char resource[] = "Ressource: ";
    char *content;
    char *url;
    char clientid[] = "Client ID: ";

    char *request = malloc(4096);

    int get = 0;

    while(fgets(request, 4096, datastream) != 0){
      	printf("Anfrage: %s", request);

      	if(get == 0){
      	char * a = NULL, *b = NULL;
        // Suche nach GET und merken der Position in a
        if ((a = strstr(request, "GET")) > 0)
			get = 1;
        else{
           	printf("! Invalid Request\n");
           	fputs(InvReq, datastream);
           	return -1;
        }
        // Suche nach HTTP Version und merken der Position in b
        if ((b = strstr(request, "HTTP/1.1")) <= 0){
            printf("#HTTP/1.1 505 HTTP Version Not Supported\n");
            fputs(WrongVersion, datastream);
            return -1;
        }

        a+=4; //stelle der resource
        content = malloc(b-a+1);
        bzero(content, b-a+1);

        strncpy(content, a, b-a);
        printf("Ressource: %s\n", content);

        }
        if(strstr(request, "Host:") > 0){
        	printf("#Host gefunden.\n");
        	url = malloc(strlen(request) + 1);
        	strcpy(url, request);
        	printf("#URL = %s\n", url);
        }

        if (strlen(request) <= 2){
        	printf("#Anfrage entgegengenommen.\n");
        	break;
        }
    }

    // wenn url == NULL wurde "Host:" nicht gefunden
  	if (url == NULL){
      fputs(NoHost, datastream);
      free(url);
      return -1;
    }

  	free(url);
  	free(request);

	fputs("HTTP/1.1 200 OK\r\n", datastream);
  	fputs(header, datastream);
  	fputs(resource, datastream); 
  	fputs(content, datastream);
  	free(content);
  	fputs("\r\n", datastream);
  	fputs(clientid, datastream); 
  	fputs(information, datastream);
  	fputs("\r\n", datastream);


	return 0;
}