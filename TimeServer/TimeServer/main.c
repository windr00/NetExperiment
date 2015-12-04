//
//  main.c
//  EchoServer
//
//  Created by WindR on 15/11/26.
//  Copyright © 2015年 WindR. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_SEND_BYTES 4096
#define MAX_RECV_BYTES 4096
#define UDP 17


int main (int argc, char ** argv) {
    int sock = -1;
    
    char recvBuffer[MAX_RECV_BYTES] = {0};
    
    long recvLength = 0;
    
    int port = 12321;
    
    long sysTime = 0;
    
    struct sockaddr_in sockAddress;
    memset(&sockAddress, 0, sizeof(sockAddress));
    
    
    if ((sock = socket(AF_INET, SOCK_DGRAM, UDP)) < 0) {
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
    
    
    struct sockaddr_in clientAddress;
    memset(&clientAddress, 0, sizeof(clientAddress));
    socklen_t len = sizeof(clientAddress);
    
    printf("server ready on port %d\n", port);
    
    
    while (1) {
        if ((recvLength = recvfrom(sock, recvBuffer, MAX_RECV_BYTES, 0, (struct sockaddr *)&clientAddress, &len)) < 0) {
            printf("receive error\n");
            continue;
        }
        
        
        
        recvBuffer[recvLength] = '\0';
        
        printf("recieved: %s\n",recvBuffer);
        
        if (strcmp(recvBuffer, "TIME") == 0) {
            sysTime = time(NULL);
            sprintf(recvBuffer, "%ld", sysTime);
            if (sendto(sock, recvBuffer, strlen(recvBuffer), 0, (struct sockaddr *)&clientAddress, sizeof(clientAddress)) != strlen(recvBuffer)) {
                printf("send error\n");
                continue;
            }
        }
    }
    return 0;
}