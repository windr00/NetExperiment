//
//  includes.h
//  TCPChatServer
//
//  Created by 冉惟之 on 15/11/26.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#ifndef includes_h
#define includes_h
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "SocketConnection.h"
#include "UserArray.h"
#include "SocketConnectionKeep.h"
#include "Support.h"
#include "SocketOpration.h"

#define MAX_SEND_BYTES 4096
#define MAX_RECV_BYTES 4096
#define TCP 6





#endif /* includes_h */
