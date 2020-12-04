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

void ssend(int sock, char* msg, int msg_len, struct sockaddr* addr, int addr_size){
	if(sendto(sock, msg, msg_len, 0, addr, addr_size) != msg_len){
		errorHandler("[-]ssend() fail");
		close(sock);
		clearWinSock();
	}
}
void srecv(int sock, char* buffer, int buf_len, struct sockaddr* addr, int* addr_size){
	if(recvfrom(sock, buffer, buf_len, 0, addr, addr_size) < 0){
		errorHandler("[-]srecvfrom() fail...");
		close(sock);
		clearWinSock();
	}
	printf("%s", buffer);
}


