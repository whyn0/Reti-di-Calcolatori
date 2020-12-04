/*
 ============================================================================
 Name        : serverUDP.c
 Author      : Gianluca Parisi
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "commonlib.h"

void removeVowels(char* str);

int main(void) {
#if	defined	WIN32
	WSADATA	wsaData;
	int	iResult	= WSAStartup(MAKEWORD(2,2),	&wsaData);
	if	(iResult !=	0)	{
		printf("Error	at	WSAStartup()\n");
		return	EXIT_FAILURE;
	}
#endif

	int server_sock;
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClntAddr;
	struct hostent *host;
	unsigned int cliAddrLen;
	char echoBuffer[ECHOMAX] = {'\0'};
	int recvMsgSize;

	if((server_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		errorHandler("[-]socket() creation failed ...");
		return -1;
	}

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_port = htons(PORT);
	echoServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// BIND DELLA SOCKET
	if ((bind(server_sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr))) < 0)
		errorHandler("[-]bind() failed");

	while(1){
		cliAddrLen = sizeof(echoClntAddr);
		//RICEVO HELLO DAL CLIENT
		srecv(server_sock, echoBuffer,  ECHOMAX, (struct sockaddr*)&echoClntAddr, &cliAddrLen);

		host = gethostbyaddr((const char*) &echoClntAddr.sin_addr, sizeof(echoClntAddr.sin_addr), AF_INET);

		printf("[+]Ricevuti dati dal client di nome: %s e di indirizzo: %s\n", host->h_name, inet_ntoa(echoClntAddr.sin_addr));

		srecv(server_sock, echoBuffer,  ECHOMAX, (struct sockaddr*)&echoClntAddr, &cliAddrLen);

		removeVowels(echoBuffer);

		ssend(server_sock, echoBuffer, strlen(echoBuffer), (struct sockaddr*)&echoClntAddr, cliAddrLen);
	}


	clearWinSock();
	return EXIT_SUCCESS;
}

void removeVowels(char* str){
	int i;
	int j = 0;
	char* str1 = malloc(strlen(str) * sizeof(char) + 1);
	for(i = 0; i < strlen(str); i++){
		if(str[i] != 'a' && str[i] != 'e' && str[i] != 'i' && str[i] != 'o' && str[i] != 'u'){
			str1[j] = str[i];
			j++;
		}
	}
	memset((str1 + j), '\0', 1);
	strcpy(str, str1);
}
