//
//  SocketOpration.h
//  TCPChatServer
//
//  Created by WindR on 15/12/4.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#ifndef SocketOpration_h
#define SocketOpration_h
#include "includes.h"

void ReceiveData(int clientSock, char * buffer) ;

void SendData(int clientSock, const char * buffer);

#endif /* SocketOpration_h */
