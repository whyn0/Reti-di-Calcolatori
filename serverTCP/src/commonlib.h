/*
 * server.h
 *
 *  Created on: 11 nov 2020
 *      Author: whyno
 */

#ifndef COMMONLIB_H_
#define COMMONLIB_H_
#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#define PORT 12345 // default protocol port number
#define QLEN 10
#define BUFFERSIZE 512

#endif /* COMMONLIB_H_ */

//prototypes

void clearWinSock();
void errorHandler(const char *errorMessage);
int sendAll(int socket, void* buffer);
int recvAll(int socket, void* buffer);
char* srecv(int socket);
void ssend(int socket, void* buffer);
void ssrecv(int socket, void* buffer, int size);
//int recvInt(int socket);
//void sendInt(int socket, int n);
