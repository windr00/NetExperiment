//
//  UserArray.h
//  TCPChatServer
//
//  Created by 冉惟之 on 15/11/26.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#ifndef UserArray_h
#define UserArray_h

#include "includes.h"

struct User {
    int clientSockNumber;
    char * name;
    char * tempData;
};

static struct User userArray[256];


void InsertUser(const char * name, int *number, int clientSockNumber);

void DeleteUser(int number);

int JudgeUserExistence(int number);

int JudgeIfHasEmptySlot();

int GetUserAddress(int number);

char * GetUserName (int number);

char * GetAllOnlineUserName();

void InsertReceivedDataToUser(int number, const char * receivedData);

char * GetUserReceivedData (int number);

void ClearUserReceivedData (int number);

int * GetAllOnlineUserNumber (int * count);

#endif /* UserArray_h */
