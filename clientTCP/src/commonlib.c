/*
 * commonlib.c
 *
 *  Created on: 12 nov 2020
 *      Author: whyno
 */


/*
 *
 * commonlib.h implementation
 *
 */

#include "commonlib.h"

void errorHandler(const char *errorMessage){
	printf("%s", errorMessage);
}

void clearWinSock(){
#if defined WIN32
	WSACleanup();
#endif
}

int sendAll(int socket, void* buffer){
	char *ptr = (char*) buffer;//cast
	char *len;
	//sprintf(len, "%lu", strlen(ptr));
	int lenght = strlen(ptr);
	if(send(socket, &lenght, sizeof(int),0) < 0){
		printf("[-]sendAll lenght error...");
		return -1;
	} else{
		//send msg
		if(send(socket, ptr, strlen(ptr),0) < 0){
			printf("[-]sendAll msg error...");
			return -1;
		}
	}
	return 1;

}
int recvAll(int socket, void* buffer){
	int len_buf;
	int bytesRcv;
	//ricevo lunghezza
	if((bytesRcv = recv(socket, &len_buf, BUFFERSIZE - 1, 0)) < 0){
		printf("[-]recvAll lenght error...");
		return -1;
	} else {
		//int buf_len = atoi(len_buf);
		char *ptr = (char*) buffer;
		if((bytesRcv = recv(socket, ptr, len_buf - 1, 0)) < 0){
			printf("[-]recvAll msg error");
			return -1;
		}
		return 1;
	}
}
void ssend(int socket, void* buffer){
	char* ptr = (char*) buffer;
	if (send(socket, ptr, strlen(ptr), 0) != strlen(ptr)) {
		errorHandler("[-]Send operation failed...");
		close(socket);
		clearWinSock();
	}
}
char* srecv(int socket){
    char buffer[BUFFERSIZE];
    int b_rec = 0;

	if((b_rec = recv(socket, buffer, BUFFERSIZE - 1, 0)) < 0){
		errorHandler("[-]Recv operation failed...");
		close(socket);
		clearWinSock();
		return NULL;
	}
	buffer[b_rec] = '\0';
	char *result = (char *) malloc(sizeof(char) * strlen(buffer));
	strcpy(result, buffer);

	return result;
}
void sendInt(int socket, int n){
	if(send(socket, &n, sizeof(int), 0) != sizeof(int)){
		errorHandler("[-]Send operation failed...");
		close(socket);
		clearWinSock();
	}
}
int recvInt(int socket){
	int b_rec = 0;
	int n = 0;
	if((b_rec = recv(socket, &n, sizeof(int), 0)) < 0){
		errorHandler("[-]Recv operation failed...");
		close(socket);
		clearWinSock();
	}
	return n;
}

