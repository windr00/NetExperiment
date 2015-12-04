//
//  SocketOpration.c
//  TCPChatServer
//
//  Created by WindR on 15/12/4.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#include "SocketOpration.h"

void ReceiveData(int clientSock, char * buffer){
    int recvLength = 0;
    if ((recvLength = recv(clientSock, buffer, MAX_RECV_BYTES, 0) < 0)) {
        printf("client sock: %d recv error\n",clientSock);
        exit(-1);
    }
    buffer[recvLength] = '\0';
}

void SendData(int clientSock, const char * buffer) {
    long sendLength = 0;
    if ((sendLength = send(clientSock, buffer, strlen(buffer), 0)) < 0){
        printf("client sock: %d send failed\n", clientSock);
        exit(-1);
    }
}