//
//  SocketConnection.c
//  TCPChatServer
//
//  Created by 冉惟之 on 15/11/26.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#include "SocketConnection.h"


char recvBuffer[MAX_RECV_BYTES] = {0};

char sendBuffer[MAX_SEND_BYTES] = {0};

void * sendLoop (void * arg) {
    while (1) {
        system("sleep 1");
        int count = 0;
        int * array = GetAllOnlineUserNumber(&count);
        //printf("sendLoop: loop\n");
        for (int i = 0;i < count;i++) {
            SendData(GetUserAddress(array[i]), GetUserReceivedData(array[i]));
            ClearUserReceivedData(array[i]);
        }
    }
    return NULL;
}

int InitialServer() {
    memset(&serverSockAddress, 0, sizeof(serverSockAddress));
    
    sockLength = sizeof(serverSockAddress);
    
    
    
    memset(&clientAddress, 0, sizeof(clientAddress));
    clientSockLength = sizeof(clientAddress);
    
    InitialUserArray();
    
    if ((serverSock = socket(AF_INET, SOCK_STREAM, TCP)) < 0) {
        printf("socket create error\n");
        return -1;
    }
    
    printf("enter server port ");
    
    scanf("%d",&port);
    
    serverSockAddress.sin_family = AF_INET;
    serverSockAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverSockAddress.sin_port = htons(port);
    
    if (bind(serverSock, (struct sockaddr *)&serverSockAddress, sizeof(serverSockAddress)) < 0) {
        printf("bind error\n");
        return -2;
    }
    
    printf("bind succeeded\n");
    
    if (listen(serverSock, 256) == -1) {
        printf("listen error\n");
        return -3;
    }
    
    printf("start listening on port %d\n", port);
    
    pthread_t sendThread;
    if (pthread_create(&sendThread, NULL, sendLoop, NULL)) {
        printf("send loop thread creation failed.\n");
        exit(-4);
    }
    
    printf("start accepting\n");
    
    while (1) {
        
        if ((clientSock = accept(serverSock, (struct sockaddr *)&clientAddress, &clientSockLength)) == -1) {
            printf("accept error\n");
            continue;
        }
        printf("accepted: %d\n", clientSock);
        pthread_t acceptThread;
        pthread_create(&acceptThread, NULL, DispatchConnection, &clientSock);
    }
}



