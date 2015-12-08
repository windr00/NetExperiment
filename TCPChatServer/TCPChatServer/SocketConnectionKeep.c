//
//  SocketConnectionKeep.c
//  TCPChatServer
//
//  Created by 冉惟之 on 15/11/27.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#include "SocketConnectionKeep.h"

char RecvBuffer[MAX_RECV_BYTES];

char SendBuffer[MAX_SEND_BYTES];

const char * CLIENT_CONNECTION_STR = "CONNECTION";

const char * CLIENT_NAME_STR = "NAME";

const char * CLIENT_REFUSE_STR = "NO";

const char * CLIENT_ACCEPT_STR = "OK";

const char * CLIENT_REQUEST_NAME_LIST = "LIST";

const char * CLIENT_SENT_TO = "TO";

const char * CLIENT_QUIT = "QUIT";

void DoControl(int arrayNumber) {
    printf("doControl: user entered ONLINE mode, client number in user array: %d\n", arrayNumber);
    while (1) {
        ReceiveData(GetUserAddress(arrayNumber), RecvBuffer);
        if (strcmp(RecvBuffer, CLIENT_REQUEST_NAME_LIST) == 0) {
            sprintf(SendBuffer, "USER LIST \n%s", GetAllOnlineUserName());
            SendData(GetUserAddress(arrayNumber), SendBuffer);
        }
        else if (strcmp(StrCut(RecvBuffer, 0, strlen(CLIENT_SENT_TO)), CLIENT_SENT_TO) == 0) {
            int targetNUmber = 0;
            char str[MAX_RECV_BYTES] = {0};
            sscanf(StrCut(RecvBuffer, strlen(CLIENT_SENT_TO) + 1, strlen(RecvBuffer) - strlen(CLIENT_SENT_TO) - 1), "%d%s", &targetNUmber,RecvBuffer);
            if (!JudgeUserExistence(targetNUmber)) {
                printf("doControl: user specified by number: %d does not exist.\n", targetNUmber);
                SendData(GetUserAddress(arrayNumber), CLIENT_REFUSE_STR);
                pthread_exit(NULL);
            }
            sprintf(str, "from %s: %s\n", GetUserName(arrayNumber), RecvBuffer);
            InsertReceivedDataToUser(targetNUmber, str);
            continue;
        }
        else if (strcmp(RecvBuffer, CLIENT_QUIT)) {
            pthread_exit(NULL);
        }
    }
}

void Initial(int clientSock) {
    while (1) {
        ReceiveData(clientSock, RecvBuffer);
        if (strcmp(RecvBuffer, CLIENT_CONNECTION_STR) == 0) {
            printf("initial: connection received\n");
            if (!JudgeIfHasEmptySlot()) {
                printf("initial: no empty slot\n");
                SendData(clientSock, CLIENT_REFUSE_STR);
                pthread_exit(NULL);
            }
            else {
                printf("initial: has empty slot\n");
                SendData(clientSock, CLIENT_ACCEPT_STR);
            }
        }
        else if (strcmp(StrCut(RecvBuffer, 0, strlen(CLIENT_NAME_STR)), CLIENT_NAME_STR) == 0) {
            printf("initial: normal receive\n");
            char * name = StrCut(RecvBuffer, strlen(CLIENT_NAME_STR) + 1, strlen(RecvBuffer) - strlen(CLIENT_NAME_STR) - 1);
            printf("initial: new user name: %s\n", name);
            int arrayNumber = 0;
            InsertUser(name, &arrayNumber, clientSock);
            printf("initial: new user number: %d\n", arrayNumber);
            SendData(clientSock, CLIENT_CONNECTION_STR);
            printf("initial: user is ONLINE, socket number: %d\n", clientSock);
            DoControl(arrayNumber);
            break;
        }
        else {
            printf("initial: unknown client state\n");
            pthread_exit(NULL);
        }
        printf("initial: loop once ended\n");
    }
    
}





void * DispatchConnection(void * clientSock) {
    //if (!fork()) {
    Initial(* (int *)clientSock);
    return NULL;
    //}
}