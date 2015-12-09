//
//  Support.c
//  TCPChatServer
//
//  Created by 冉惟之 on 15/12/1.
//  Copyright © 2015年 冉惟之. All rights reserved.
//

#include "Support.h"

char * StrCut(const char * original, long startIndex, long cutLength) {
    //printf("strCut: start index: %ld, length: %ld\n", startIndex, cutLength);
    char * cut = malloc(cutLength + 1);
    memset(cut, 0, cutLength + 1);
    for (long i = 0; i < cutLength;i++) {
        cut[i] = original[i + startIndex];
    }
    //printf("strCut: result: '%s'\n", cut);
    return cut;
}