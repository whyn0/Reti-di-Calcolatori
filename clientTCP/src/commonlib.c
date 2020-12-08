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
	if (send(socket, ptr, strlen(ptr) + 1, 0) != (strlen(ptr) + 1)) {
		errorHandler("[-]Send operation failed...");
		closesocket(socket);
		clearWinSock();
	}
}
char* srecv(int socket){
    char buffer[BUFFERSIZE] = {'\0'};
    int b_rec = 0;

	if((b_rec = recv(socket, buffer, BUFFERSIZE, 0)) < 0){
		errorHandler("[-]Recv operation failed...");
		closesocket(socket);
		clearWinSock();
		return NULL;
	}
	char *result = malloc(sizeof(char) * strlen(buffer));
	strcpy(result, buffer);

	return result;
}
void ssrecv(int socket, void* buffer, int size){
	int b_rec = 0;
	if((b_rec = recv(socket, (char*)buffer, size, 0)) < 0 ){
		errorHandler("[-]Recv operation failed...");
		closesocket(socket);
		clearWinSock();
	}
}
void sendInt(int socket, int num){
	char* ptr = (char*)&num;
	if (send(socket, ptr, sizeof(int), 0) != sizeof(int)) {
		errorHandler("[-]Send operation failed...");
		closesocket(socket);
		clearWinSock();
	}
}
void recInt(int socket, int* num){
	int b_rec = 0;
	if((b_rec = recv(socket, (char*)num, sizeof(int), 0)) < 0 ){
		errorHandler("[-]Recv operation failed...");
		closesocket(socket);
		clearWinSock();
	}
}
