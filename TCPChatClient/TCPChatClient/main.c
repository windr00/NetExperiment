//
//  main.c
//  TCPChatClient
//
//  Created by 冉惟之 on 15/12/2.
//  Copyright © 2015年 冉惟之. All rights reserved.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_SEND_LENGTH 4096
#define MAX_RECV_LENGTH 4096
#define TCP 6

const char * CLIENT_CONNECTION_STR = "CONNECTION";

const char * CLIENT_NAME_STR = "NAME";

const char * CLIENT_REFUSE_STR = "NO";

const char * CLIENT_ACCEPT_STR = "OK";

const char * CLIENT_REQUEST_NAME_LIST = "LIST";

const char * CLIENT_SENT_TO = "TO";

const char * CLIENT_QUIT = "QUIT";

int main(int argc, const char * argv[]) {
    int sock = -1;
    
    char ipAddress[32] = {0};
    
    char name[100] = {0};
    
    char message[MAX_SEND_LENGTH] = {0};
    
    char sendBuffer[MAX_SEND_LENGTH] = {0};
    
    char recvBuffer[MAX_RECV_LENGTH] = {0};
    
    long recvLength = -1;
    
    int port = 0;
    
    int user = 0;
    
    struct sockaddr_in sockAddress;
    memset(&sockAddress, 0, sizeof(sockAddress));
    
    if ((sock = socket(AF_INET, SOCK_STREAM, TCP) < 0)) {
        printf("socket error\n");
        return -1;
    }
    
    printf("enter server ip address: ");
    scanf("%s", ipAddress);
    printf("enter server port number: ");
    scanf("%d", &port);
    
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_port = HTONS(port);
    
    if (inet_pton(AF_INET, ipAddress, &sockAddress.sin_addr) <= 0 ) {
        printf("ip address illegal\n");
        return -2;
    }
    
    if (connect(sock, (struct sockaddr *)&sockAddress, sizeof(sockAddress)) < 0) {
        printf("connect error\n");
        return -3;
    }
    
    if (send(sock, CLIENT_CONNECTION_STR, strlen(CLIENT_CONNECTION_STR), 0) < 0) {
        printf("initial send error\n");
        return -4;
    }
    
    if ((recvLength = recv(sock, recvBuffer, MAX_RECV_LENGTH, 0)) < 0) {
        printf("initial recv error\n");
        return -5;
    }
    
    recvBuffer[recvLength] = 0;
    
    if (strcmp(recvBuffer, CLIENT_REFUSE_STR) == 0) {
        printf("server refused\n");
        return -6;
    }
    
    printf("input your user name, maximum length is 100 bytes\n");
    
    scanf("%s",name);
    
    if (send(sock, CLIENT_NAME_STR, strlen(CLIENT_NAME_STR),0) < 0) {
        printf("user name specifying error\n");
        return -10;
    }
    
    if ((recvLength = recv(sock, recvBuffer , MAX_RECV_LENGTH, 0)) < 0) {
        printf("user name comfirmation error\n");
        return -11;
    }
    
    recvBuffer[recvLength] = 0;
    
    if (strcmp(recvBuffer, CLIENT_CONNECTION_STR) != 0) {
        printf("unkown server state\n");
        return 0;
    }
    
    if (send(sock, CLIENT_REQUEST_NAME_LIST, strlen(CLIENT_REQUEST_NAME_LIST), 0) < 0) {
        printf("fetch online user error\n");
        return -7;
    }
    
    if ((recvLength = recv(sock, recvBuffer, MAX_RECV_LENGTH, 0)) < 0) {
        printf("fetch online user error\n");
        return -8;
    }
    
    recvBuffer[recvLength] = 0;
    
    printf("online users:\n");
    
    printf("%s",recvBuffer);
    
    printf("please choose a user by number: ");
    
    scanf("%d", &user);
    
    if (!fork()) {
        while (1) {
            if ((recvLength = recv(sock, recvBuffer, MAX_RECV_LENGTH, 0)) < 0) {
                continue;
            }
            recvBuffer[recvLength] = 0;
            printf("\nreceived: %s\n", recvBuffer);
        }
    }
    
    printf("input your words after '>' \n");
    
    while (1) {
        printf("> ");
        scanf("%s",message);
        sprintf(sendBuffer, "%s %d %s", CLIENT_SENT_TO, user, message);
        if (send(sock, sendBuffer, strlen(sendBuffer), 0) < 0) {
            printf("message send error\n");
            continue;
        }
    }
    return 0;
}
