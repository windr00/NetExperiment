//
//  SocketConnection.h
//  TCPChatServer
//
//  Created by 冉惟之 on 15/11/26.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#ifndef SocketConnection_h
#define SocketConnection_h

#include "includes.h"


static int serverSock = -1;

static int clientSock = -1;

static int port = 0;




static struct sockaddr_in serverSockAddress;
static struct sockaddr_in clientAddress;

static socklen_t sockLength ;
static socklen_t clientSockLength;

int InitialServer();


#endif /* SocketConnection_h */
