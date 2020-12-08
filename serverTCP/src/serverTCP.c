/*
 ============================================================================
 Name        : serverTCP.c
 Author      : Gianluca Parisi
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "commonlib.h"

int main(int argc, char* argv[]) {


	int port;
	int sock;
	struct sockaddr_in sad;//server address
	struct sockaddr_in cad;//client address
	char buffer[BUFFERSIZE] = {'\0'};

	//inizializzazione socket windows
#if defined WIN32
	//test
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(iResult != 0){
		errorHandler("[-]Error at wsastartup()\n");
		return -1;
	}
#endif
	//selecting port
	if(argc > 1){
		port = atoi(argv[1]);
	} else {
		port = PORT;
	}
	//
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0){
		errorHandler("[-]Error at socket()!\n");
		clearWinSock();
		return -1;
	}
	memset(&sad, 0 , sizeof(sad));
	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr("127.0.0.1");
	sad.sin_port = htons(port); //port binding
 //zero rest of structure

	//binding

	if(bind(sock, (struct sockaddr*)&sad, sizeof(sad)) < 0){
		errorHandler("[-]Bind() failed");
		closesocket(sock);
		clearWinSock();
		return -1;
	}

	//listen

	if(listen(sock,QLEN) < 0){
		errorHandler("[-]Listen() failed\n");
		closesocket(sock);
		clearWinSock();
		return -1;
	}

	int clientLen = sizeof(cad);
	int new_sock;//new sock
	printf("[+]Waiting for connections...\n");
	while(1){
		if ((new_sock = accept(sock, (struct sockaddr *)&cad, &clientLen)) < 0) {
		errorHandler("[-]Accept() failed.\n");
		closesocket(sock);
		clearWinSock();
		return 0;
		}
	printf("[+]Handling client %s\n", inet_ntoa(cad.sin_addr));
	//Send "connessione avvenuta to server"
	char* greet = "[+]Connessione avvenuta...";
	ssend(new_sock, greet);
	//determino l'operazione
	ssrecv(new_sock, buffer, BUFFERSIZE);
	char op = *buffer;
	op = toupper(op);
	char* str_op = malloc(50 * sizeof(char));
	if(op == 'A'){
		strcpy(str_op, "ADDIZIONE");
	} else if(op == 'S'){
		strcpy(str_op, "SOTTRAZIONE");
	} else if(op == 'M'){
		strcpy(str_op, "MOLTIPLICAZIONE");
	} else if(op == 'D'){
		strcpy(str_op, "DIVISIONE");
	} else{
		strcpy(str_op, "TERMINE PROCESSO CLIENT");
	}
	ssend(new_sock, str_op);//send stringa al client

	int num1;
	int num2;
	recInt(new_sock, &num1);
	recInt(new_sock, &num2);

	int result = 0;
	if(op == 'A'){
		result = num1 + num2;
		} else if(op == 'S'){
		result = num1 - num2;
		} else if(op == 'M'){
		result = num1 * num2;
		} else if(op == 'D'){
			if(num2 != 0){
				result = num1 / num2;
			}
		}
	sendInt(new_sock, result);
	}
	clearWinSock();
	closesocket(new_sock);
#if defined WIN32
	system("pause");
#endif

	return 0;
}
