//
//  SocketConnectionKeep.h
//  TCPChatServer
//
//  Created by 冉惟之 on 15/11/27.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#ifndef SocketConnectionKeep_h
#define SocketConnectionKeep_h

#include "includes.h"



static long recvLength = 0;

void DispatchConnection(int clientSock);

#endif /* SocketConnectionKeep_h */
