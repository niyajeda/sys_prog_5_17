#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "sock.h"
#include "handler.h"



int main(int argc, char **argv)
{
	int anzverbindungen;
	int portnummer;
	
	if (argc != 3) errx(1, "usage: %s <number_of_requests> <portnumber>", argv[0]);

	anzverbindungen = atoi(argv[1]);
	portnummer = atoi(argv[2]);

	if (prepare_socket(portnummer)) {
		printf("Fehler beim Erzeugen / binden des Sockets\n");
		return 1;
	}
	anzverbindungen = manage_connections(anzverbindungen, &manager);
	printf("%d Verbindungen wurden behandelt.\n", anzverbindungen);
	close_socket();
	return 0;
}






