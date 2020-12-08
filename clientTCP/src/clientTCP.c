/*
 ============================================================================
 Name        : clientTCP.c
 Author      : Gianluca Parisi
 Version     :
 Copyright   : 
 Description : client tcp per esonero di reti di calcolatori, testato e compilato su Ubuntu 20.04 e Windows 10
 ============================================================================
 */

#include "commonlib.h"

int main(void) {
	int sock;
	struct sockaddr_in sad;
	char buffer[BUFFERSIZE] = {'\0'};


#if defined WIN32
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(iResult != 0){
		errorHandler("[-]Error at wsastartup()...\n");
		return -1;
	}
#endif

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		errorHandler("[-]Socket creation failed...");
		closesocket(sock);
		clearWinSock();
		return -1;
	}

	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr("127.0.0.1");
	sad.sin_port = htons(PORT);
	memset(&(sad.sin_zero), 0, 8);

	//connect to server
	if (connect(sock, (struct sockaddr*) &sad, sizeof(struct sockaddr_in))
			< 0) {
		errorHandler("[-]Connection failed...");
		closesocket(sock);
		clearWinSock();
		return -1;
	}
	//receive and display greet
	ssrecv(sock, buffer, BUFFERSIZE);
	printf("%s\n", buffer);
	fflush(stdin);
	//leggo lettera dall stdin
	char op = '\0';
	printf("[+]Inserire operazione(a/s/m/d) : ");
	fflush(stdin);
	scanf("%c",&op);
	buffer[0] = op;
	buffer[1] = '\0';
	ssend(sock, buffer);
	ssrecv(sock, buffer, BUFFERSIZE);
	printf("[+]%s\n", buffer);
	int num1, num2;
	int result = 0;
	if(strcmp(buffer, "ADDIZIONE") == 0){
		printf("[+]Inserisci due numeri da addizionare(num1 num2): ");
		scanf("%d %d", &num1, &num2);
	} else if (strcmp(buffer, "SOTTRAZIONE") == 0){
		printf("[+]Inserisci due numeri da sottrarre(num1 num2): ");
		scanf("%d %d", &num1, &num2);
	} else if (strcmp(buffer, "MOLTIPLICAZIONE") == 0){
		printf("[+]Inserisci due numeri da moltiplicare(num1 num2): ");
		scanf("%d %d", &num1, &num2);
	} else if (strcmp(buffer, "DIVISIONE") == 0){
		printf("[+]Inserisci due numeri da dividere(num1 num2): ");
		scanf("%d %d", &num1, &num2);
	} else{
		printf("[-]Invalid type of operation...");
		clearWinSock();
		closesocket(sock);
		return -1;
	}
	sendInt(sock, num1);
	sendInt(sock, num2);
	recInt(sock, &result);

	printf("\n[+]Risultato: %d\n", result);

	clearWinSock();
	closesocket(sock);
#if defined WIN32
	system("pause");
#endif
	return 0;
}
