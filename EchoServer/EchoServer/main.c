//
//  main.c
//  EchoServer
//
//  Created by WindR on 15/11/26.
//  Copyright © 2015年 WindR. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_SEND_BYTES 4096
#define MAX_RECV_BYTES 4096
#define TCP 6


int main (int argc, char ** argv) {
    int sock = -1;
    
    int clientSock = -1;
    
    
    char recvBuffer[MAX_RECV_BYTES] = {0};
    
    long recvLength = 0;
    
    int port = 12321;
    
    pid_t pid = 1 ;
    
    struct sockaddr_in sockAddress;
    memset(&sockAddress, 0, sizeof(sockAddress));
    
    struct sockaddr_in clientAddress;
    memset(&clientAddress, 0, sizeof(clientAddress));
    socklen_t len = sizeof(clientAddress);
    
    if ((sock = socket(AF_INET, SOCK_STREAM, TCP)) < 0) {
        printf("socket error\n");
        return -1;
    }
    
    printf("enter server port:");
    
    scanf("%d",&port);
    
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddress.sin_port = htons(port);
    
    if (bind(sock, (struct sockaddr *) & sockAddress, sizeof(sockAddress)) < 0) {
        printf("bind error\n");
        return -2;
    }
    
    if (listen(sock, 10) == -1) {
        printf("listen error\n");
        return -3;
    }
    
    
    printf("listening on port %d\n", port);
    
    while (1) {
        if ((clientSock = accept(sock, (struct sockaddr *)&clientAddress, &len)) == -1) {
            printf("%d accept error\n", pid);
            continue;
        }
        pid = fork();
        
        if (!pid) {
            while (1) {
                recvLength = recv(clientSock, recvBuffer, MAX_RECV_BYTES, 0);
                
                recvBuffer[recvLength] = '\0';
                if (send(clientSock, recvBuffer, strlen(recvBuffer),0) < 0) {
                    printf("send error\n");
                    close (clientSock);
                    return -4;
                }
                
                printf("received: %s\nfrom: %s:%d\nclient sock: %d\n",recvBuffer,inet_ntoa(clientAddress.sin_addr),clientAddress.sin_port,clientSock);
                
                if (strcmp(recvBuffer, "Q") == 0) {
                    close(clientSock);
                    exit(0);
                }
            }
        }
    }
    return 0;
}

