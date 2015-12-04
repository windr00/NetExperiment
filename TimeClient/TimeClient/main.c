//
//  main.c
//  TimeClient
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

#define MAX_SEND_LENGTH 4096
#define MAX_RECV_LENGTH 4096
#define UDP 17

int main(int argc, char ** argv) {
    int sock = -1;
    
    char ipAddress[32] = {0};
    
    char sendBuffer[MAX_SEND_LENGTH] = {0};
    
    char recvBuffer[MAX_RECV_LENGTH] = {0};
    
    int port = 0;
    
    char answer = 0;
    
    struct sockaddr_in sockAddress;
    memset(&sockAddress, 0, sizeof(sockAddress));
    
    
    if ((sock = socket(AF_INET, SOCK_DGRAM, UDP)) < 0) {
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
    
    
    
    while (1) {
        strcpy(sendBuffer, "TIME");
        
        if (sendto(sock, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr *)&sockAddress, sizeof(sockAddress)) != strlen(sendBuffer)){
            printf("send failed\n");
            continue;
        }
        
        memset(&sockAddress, 0, sizeof(sockAddress));
        socklen_t len = sizeof(sockAddress);
        long recvLength = 0;
        
        
        if ((recvLength = recvfrom(sock, recvBuffer, MAX_RECV_LENGTH, 0, (struct sockaddr * )&sockAddress, &len)) < 0) {
            printf("receive failed\n");
            continue;
        }
        
        recvBuffer[recvLength] = '\0';
        
        printf("received unix standard time: %s\n", recvBuffer);
        printf("input c to try again, input q to quit\n");
        getchar();
        scanf("%c",&answer);
        
        switch (answer) {
            case 'c':
                continue;
                break;
            case 'q':
                close(sock);
                return 0;
                break;
            default:
                break;
        }
    }
    
    return 0;
}