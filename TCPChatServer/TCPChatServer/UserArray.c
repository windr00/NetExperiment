//
//  UserArray.c
//  TCPChatServer
//
//  Created by 冉惟之 on 15/11/26.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#include "UserArray.h"


void InsertUser(const char * name, int *number, int clientSockNumber) {
    int i = 0;
    for (i = 0;i < 256;i++) {
        if (userArray[i].clientSockNumber == -1) {
            *number = i;
            userArray[i].clientSockNumber = clientSockNumber;
            strcpy(userArray[i].name, name);
            char * temp = malloc(2);
            strcpy(temp, "");
            userArray[i].tempData = temp;
        }
    }
}

int JudgeIfHasEmptySlot() {
    for (int i = 0;i < 256;i++) {
        if (userArray[i].clientSockNumber == -1) {
            return 1;
        }
    }
    return 0;
}

void DeleteUser(int number) {
    userArray[number].clientSockNumber = -1;
    free(userArray[number].name);
}

int JudgeUserExistence(int number) {
    if (userArray[number].clientSockNumber == -1) {
        return 1;
    }
    return 0;
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
        if (userArray[i].name != NULL) {
            char tempStr[4096];
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
    char * temp = userArray[number].tempData;
    userArray[number].tempData = malloc(strlen(temp) + strlen(receivedData) + 1);
    memset(userArray[number].tempData, 0, strlen(temp) + strlen(receivedData) + 1);
    strcat(userArray[number].tempData, temp);
    strcat(userArray[number].tempData, receivedData);
}

char * GetUserReceivedData (int number) {
    return userArray[number].tempData;
}

void ClearUserReceivedData (int number) {
    free(userArray[number].tempData);
    char * temp = malloc(2);
    strcpy(temp, "");
    userArray[number].tempData = temp;
}

int * GetAllOnlineUserNumber (int * count) {
    int * array = malloc(sizeof(int) * 1);
    int * temp = NULL;
    int c = 0;
    for (int i = 0;i < 256;i++) {
        if (userArray[i].tempData) {
            c++;
            temp = array;
            array = malloc(sizeof(int) * (c + 1));
            for (int i = 0;i < c;i++) {
                array[i] = temp[i];
            }
            free(temp);
            array[c] = i;
        }
    }
    * count = c;
    return array;
}