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

void Initial(int clientSock) {
    
    ReceiveData(clientSock, RecvBuffer);
    if (strcmp(RecvBuffer, CLIENT_CONNECTION_STR) == 0) {
        if (!JudgeIfHasEmptySlot()) {
            SendData(clientSock, CLIENT_REFUSE_STR);
            exit(0);
        }
        else {
            SendData(clientSock, CLIENT_ACCEPT_STR);
        }
    }
    else if (strcmp(StrCut(RecvBuffer, 0, strlen(CLIENT_NAME_STR)), CLIENT_NAME_STR) == 0) {
        char * name = StrCut(RecvBuffer, (int)strlen(CLIENT_NAME_STR), strlen(RecvBuffer) - strlen(CLIENT_NAME_STR));
        int arrayNumber = 0;
        InsertUser(name, &arrayNumber, clientSock);
        SendData(clientSock, CLIENT_CONNECTION_STR);
        
    }
}


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




void DispatchConnection(int clientSock) {
    if (!fork()) {
        Initial(clientSock);
    }
}