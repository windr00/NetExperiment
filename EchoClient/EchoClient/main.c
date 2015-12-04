//
//  main.c
//  EchoClient
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

int main(int argc, char ** argv) {
    int sock = -1;
    
    char ipAddress[32] = {0};
    
    char sendBuffer[MAX_SEND_BYTES] = {0};
    
    char recvBuffer[MAX_RECV_BYTES] = {0};
    
    int port = 0;
    
    struct sockaddr_in sockAddress;
    memset(&sockAddress, 0, sizeof(sockAddress));
    
    
    if ((sock = socket(AF_INET, SOCK_STREAM, TCP)) < 0) {
        printf("socket error\n");
        return -1;
    }
    
    printf("enter server ip address: ");
    scanf("%s",ipAddress);
    printf("enter server port number: ");
    scanf("%d", &port);
    
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_port = htons(port);
    
    if (inet_pton(AF_INET, ipAddress, &sockAddress.sin_addr) <= 0) {
        printf("ip address error\n");
        return -2;
    }
    
    if (connect(sock, (struct sockaddr *)&sockAddress, sizeof(sockAddress)) < 0) {
        printf("connect error\n");
        return -3;
    }
    
    
    while (1) {
        printf("input your massage (maximum length is 4096 bytes, input Q to quit):\n");
        fflush(stdin);
        scanf("%s",sendBuffer);
        
        
        if ( send(sock, sendBuffer, strlen(sendBuffer), 0) < 0) {
            printf("send error\n");
            return -4;
        }
        
        if (recv(sock, recvBuffer, 4096, 0) < 0) {
            printf("recv error\n");
            return -5;
        }
        
        printf("received: %s\n", recvBuffer);
        
        if (strcmp("Q", sendBuffer) == 0) {
            break;
        }
    }
    
    close(sock);
    return 0;
}