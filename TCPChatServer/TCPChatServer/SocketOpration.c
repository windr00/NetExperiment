//
//  SocketOpration.c
//  TCPChatServer
//
//  Created by WindR on 15/12/4.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#include "SocketOpration.h"

void ReceiveData(int clientSock, char * buffer){
    if (recv(clientSock, buffer, MAX_RECV_BYTES, 0) < 0) {
        printf("client sock: %d recv error\n",clientSock);
        exit(-1);
    }
    printf("length: %ld\n", strlen(buffer));
    buffer[strlen(buffer) - 2] = 0;
    printf("recv from %d content: %s\n", clientSock, buffer);
}

void SendData(int clientSock, const char * buffer) {
    long sendLength = 0;
    printf("send to: %d content: %s\n", clientSock, buffer);
    if ((sendLength = send(clientSock, buffer, strlen(buffer), 0)) < 0){
        printf("client sock: %d send failed\n", clientSock);
        exit(-1);
    }
}