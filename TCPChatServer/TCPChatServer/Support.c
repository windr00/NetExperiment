//
//  Support.c
//  TCPChatServer
//
//  Created by 冉惟之 on 15/12/1.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#include "Support.h"

char * StrCut(const char * original, int startIndex, long cutLength) {
    char * cut = malloc(cutLength + 1);
    for (long i = startIndex; i < cutLength;i++) {
        cut[i - startIndex] = original[i];
    }
    cut[cutLength] = 0;
    return cut;
}