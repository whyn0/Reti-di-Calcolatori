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
#include <windows.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#endif /* COMMONLIB_H_ */

#define ECHOMAX 512


//prototypes

void clearWinSock();
void errorHandler(const char *errorMessage);
void ssend(int sock, char* msg, int msg_len, struct sockaddr* addr, int addr_size);
void srecv(int sock, char* buffer, int buf_len, struct sockaddr* addr, int* addr_size);

