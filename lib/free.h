#ifndef __FREE_H__
#define __FREE_H__

#include <stdlib.h>

int freeList(char **list, int listC){

    if (list){
        for (int i = 0; i < listC; i++)
            if (list[i])    free(list[i]);
            else            break;
    }
    
    return 0;
}

#endif