/*
 ============================================================================
 Name        : clientUDP.c
 Author      : Gianluca Parisi
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "commonlib.h"


int main(void) {
#if	defined	WIN32
	WSADATA	wsaData;
	int	iResult	= WSAStartup(MAKEWORD(2,2),	&wsaData);
	if	(iResult !=	0)	{
		printf("Error	at	WSAStartup()\n");
		return	EXIT_FAILURE;
	}
#endif

	struct hostent *host;
	struct hostent *serv;
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[ECHOMAX] = {'\0'};

	char* hostname = malloc(20 * sizeof(char));
	int port = 0;

	printf("[+]Inserire il nome dell'host: ");
	scanf("%s", hostname);
	printf("[+]Inserire il numero di porta: ");
	scanf("%d", &port);

    if((client_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        errorHandler("[-]Impossibile creare il socket client");
        return -1;
    }

	host = gethostbyname(hostname);

	if	(host == NULL)	{
		fprintf(stderr,	"[-]gethostbyname() failed.\n");
		exit(EXIT_FAILURE);
	}
	struct in_addr* ina = (struct in_addr*) host->h_addr_list[0];

	//serverAddress filling
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = ina->s_addr;
	//
	char* hello = "Hello!\n";
	int saddlen = sizeof(server_address);
	ssend(client_socket, hello, strlen(hello), (struct sockaddr* )&server_address, sizeof(server_address));
	//leggi stringa da stdin
	scanf("%s", buffer);
	char* str = malloc(strlen(buffer) * sizeof(char) + 1);
	strcpy(str, buffer);
	//invia stringa al server
	ssend(client_socket, str, strlen(str), (struct sockaddr* )&server_address, sizeof(server_address));
	//riceve stringa senza vocali dal server
	srecv(client_socket, buffer, strlen(buffer), (struct sockaddr* )&server_address, &saddlen);
	free(str);
	str = malloc(strlen(buffer) * sizeof(char) + 1);
	strcpy(str, buffer);
	serv = gethostbyaddr((const char *)&server_address.sin_addr, sizeof(server_address.sin_addr), AF_INET);
	printf("Stringa %s ricevuta dal server di nome: %s e indirizzo: %s\n", str, serv->h_name, inet_ntoa(server_address.sin_addr));

	clearWinSock();
	return EXIT_SUCCESS;
}

