//
//  UserArray.c
//  TCPChatServer
//
//  Created by 冉惟之 on 15/11/26.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#include "UserArray.h"

void InitialUserArray() {
    for (int i = 0; i < 256;i++) {
        userArray[i].clientSockNumber = -1;
        memset(userArray[i].name, 0, MAX_RECV_BYTES);
        memset(userArray[i].tempData, 0, MAX_RECV_BYTES);
    }
}


void InsertUser(const char * name, int *number, int clientSockNumber) {
    int i = 0;
    for (i = 0;i < 256;i++) {
        if (userArray[i].clientSockNumber == -1) {
            *number = i;
            userArray[i].clientSockNumber = clientSockNumber;
            strcpy(userArray[i].name, name);
            printf("insertUser: socket: %d, array number: %d\n", clientSockNumber, *number);
            break;
        }
    }
}

int JudgeIfHasEmptySlot() {
    for (int i = 0;i < 256;i++) {
        if (userArray[i].clientSockNumber == -1) {
            printf("has empty user slot\n");
            return 1;
        }
    }
    return 0;
}

void DeleteUser(int number) {
    userArray[number].clientSockNumber = -1;
    memset(userArray[number].name, 0, MAX_RECV_BYTES);
    memset(userArray[number].tempData, 0, MAX_RECV_BYTES);
}

int JudgeUserExistence(int number) {
    if (userArray[number].clientSockNumber == -1) {
        printf("judgeUserExistence: user with number: %d does not exist.\n", number);
        return 0;
    }
    return 1;
}

int GetUserAddress(int number) {
    return userArray[number].clientSockNumber;
}

char * GetUserName (int number) {
    return userArray[number].name;
}

char * GetAllOnlineUserName() {
    char * retValue = malloc(1);
    memset(retValue, 0, 1);
    char * temp = NULL;
    for (int i = 0;i < 256;i++) {
        if (userArray[i].clientSockNumber != -1) {
            char tempStr[MAX_RECV_BYTES];
            sprintf(tempStr, "%d %s\n",i,userArray[i].name);
            temp = retValue;
            retValue = malloc(strlen(temp) + strlen(tempStr) + 1);
            memset(retValue, 0, strlen(temp) + strlen(tempStr)+ 1);
            strcat(retValue, temp);
            strcat(retValue, tempStr);
        }
    }
    
    return retValue;
}

void InsertReceivedDataToUser(int number, const char * receivedData) {
    strcat(userArray[number].tempData, receivedData);
    printf("insertReceivedDataToUser: user number: %d, total data: %s\n", number, userArray[number].tempData);
}

char * GetUserReceivedData (int number) {
    return userArray[number].tempData;
}

void ClearUserReceivedData (int number) {
    //printf("clearUserReceivedData: data of number: %d cleared\n", number);
    memset(userArray[number].tempData, 0, MAX_RECV_BYTES);
}

int * GetAllOnlineUserNumber (int * count) {
    int array[256] = {0};
    int * temp = NULL;
    int c = 0;
    for (int i = 0;i < 256;i++) {
        if (userArray[i].clientSockNumber != -1) {
            c++;
            array[c] = i;
        }
    }
    //printf("getAllOnlineUserNumber: result count: %d\n", c);
    * count = c;
    temp = (int *)malloc(sizeof(int) * c);
    for (int i = 0;i < c;i++) {
        temp[i] = array[i];
    }
    return temp;
}