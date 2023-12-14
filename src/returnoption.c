#include <string.h>

#include "../include/returnoption.h"

#define MAX_DATA 100

int returnOption(int argc, char *argv[]){
	//옵션 위치 찾기
	for(int m = 0; m < argc; m++)
		if(strstr(argv[m], "-o") != NULL) return m;
	
	return 0;
}


