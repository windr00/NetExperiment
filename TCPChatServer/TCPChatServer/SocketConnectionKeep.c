//
//  SocketConnectionKeep.c
//  TCPChatServer
//
//  Created by 冉惟之 on 15/11/27.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#include "SocketConnectionKeep.h"

char RecvBuffer[MAX_RECV_BYTES];

const char * CLIENT_CONNECTION_STR = "CONNECTION";

const char * CLIENT_NAME_STR = "NAME";

const char * CLIENT_REFUSE_STR = "NO";

const char * CLIENT_ACCEPT_STR = "OK";

const char * CLIENT_REQUEST_NAME_LIST = "LIST";

const char * CLIENT_SENT_TO = "TO";

const char * CLIENT_QUIT = "QUIT";

void DoControl(int arrayNumber) {
    while (1) {
        ReceiveData(GetUserAddress(arrayNumber), RecvBuffer);
        if (strcmp(RecvBuffer, CLIENT_REQUEST_NAME_LIST) == 0) {
            SendData(GetUserAddress(arrayNumber), GetAllOnlineUserName());
        }
        else if (strcmp(StrCut(RecvBuffer, 0, strlen(CLIENT_SENT_TO)), CLIENT_SENT_TO) == 0) {
            int targetNUmber = 0;
            sscanf(StrCut(RecvBuffer, (int)strlen(CLIENT_SENT_TO), strlen(RecvBuffer) - strlen(CLIENT_SENT_TO)), "%d", &targetNUmber);
            if (!JudgeUserExistence(targetNUmber)) {
                SendData(GetUserAddress(arrayNumber), CLIENT_REFUSE_STR);
                continue;
            }
            InsertReceivedDataToUser(targetNUmber, RecvBuffer);
            continue;
        }
        else if (strcmp(RecvBuffer, CLIENT_QUIT)) {
            exit(0);
        }
    }
}

void Initial(int clientSock) {
    while (1) {
        ReceiveData(clientSock, RecvBuffer);
        printf("%ld, %ld\n", strlen(RecvBuffer), strlen(CLIENT_CONNECTION_STR));
        if (strcmp(RecvBuffer, CLIENT_CONNECTION_STR) == 0) {
            printf("connection received\n");
            if (!JudgeIfHasEmptySlot()) {
                printf("no empty slot\n");
                SendData(clientSock, CLIENT_REFUSE_STR);
                exit(0);
            }
            else {
                printf("initial\n");
                SendData(clientSock, CLIENT_ACCEPT_STR);
            }
        }
        else if (strcmp(StrCut(RecvBuffer, 0, strlen(CLIENT_NAME_STR)), CLIENT_NAME_STR) == 0) {
            printf("normal receive\n");
            char * name = StrCut(RecvBuffer, (int)strlen(CLIENT_NAME_STR), strlen(RecvBuffer) - strlen(CLIENT_NAME_STR));
            printf("new user name: %s\n", name);
            int arrayNumber = 0;
            InsertUser(name, &arrayNumber, clientSock);
            printf("new user number: %d\n", arrayNumber);
            SendData(clientSock, CLIENT_CONNECTION_STR);
            printf("initial returned\n");
            DoControl(arrayNumber);
            break;
        }
        printf("do nothing\n");
    }
    
}





void DispatchConnection(int clientSock) {
    if (!fork()) {
        Initial(clientSock);
    }
}