#ifndef __READWILDFILE_H__
#define __READWILDFILE_H__

#include <stdio.h>
#include <stdlib.h>

#include "../include/readwild.h"

char **readWildFile(int *wildFileListC){

	FILE *file 				= NULL; //logfind의 파일 포인터
	char **wildFileList 	= NULL; //return할 wildFileList
	char *line 				= NULL; //logfind의 라인 내용; ex) logfind의 1번째 라인: *.py\n -> line변수: *.py\n
    int lineCount 			= 0; 	//logfind의 라인 수 == wildFileListC;  루프용 인덱스 변수 
	int size 				= 0; 	//wildFileList의 메모리 크기
    int i					= 0; 	//루프용 인덱스 변수
	size_t len 				= 0; 	//함수 인수용 변수
    size_t read 			= 0; 	//logfind의 각 라인의 문자수 ex) logfind의 1번째 라인: *.py\n -> read변수:  


    //.logfind 파일 오픈 
	file = fopen(".logfind","r");
	if(file == NULL){
		printf("None of .logfind, create .logfind first.\n");
		goto error;
	}

    	//읽어 오는 파일 목록 크기 추출
    	while( ( read = getline(&line, &len, file) ) != -1 ) {    

        
			size 	= sizeof(char*) * ++lineCount;
			i 	 	= lineCount - 1;

			//목록 배열 재할당 2차원
			wildFileList = (char**) realloc(wildFileList, size);
        		if(wildFileList == NULL) 
					goto error;
        
			//목록 배열 할당 1차원
			wildFileList[i] = (char*)malloc(sizeof(char) * read);
        		if(wildFileList[i] == NULL) 
					goto error;

        	//목록 배열에 읽어 온 파일 목록 저장 및 개행문자에서 널문자로 교체
        	strcpy(wildFileList[i], line);
        	wildFileList[i][strlen(wildFileList[i]) - 1] = '\0';
    	}


    //읽어 온 파일 목록 크기 리턴
	*wildFileListC = lineCount;


	fclose(file);
	return wildFileList;

error:
	if (file) fclose(file);
	return wildFileList;

}

#endif
