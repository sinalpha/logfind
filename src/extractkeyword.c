#include <stdlib.h>
#include <string.h>

#include "../include/extractkeyword.h"

#define MAX_DATA 100

char** extractKeyword(int argc, char* argv[], int option, int* keywordListC){

    //인수 오류 걸러내기
    if(argv == NULL || keywordListC == NULL) return NULL;

    if(argc < 0 || option < 0) return NULL;


    //변수 정의
	char **keywordList 	= NULL;
	int keywordC 		= 0; //키워드 갯수; keywordListC는 keywordList의 크기다


    //키워드가 최대 최대 문자열 이하인지 점검
	for(int i = 0; i < argc; i++)
			if(strlen(argv[i]) == MAX_DATA) goto error;


    //키워드 갯수; 옵션 있음 -> -2, 옵션 없음 -> -1
	if(option) 	keywordC = argc - 2;
	else 		keywordC = argc - 1;
	
	*keywordListC = keywordC; 	//키워드 갯수 리턴


    //리턴할 2차원 메모리 할당
	keywordList = (char**)malloc(sizeof(char*) * keywordC );
	if (keywordList == NULL)  goto error;


    //리턴할 1차원 메모리 할당
	for(int i = 0; i < keywordC; i++){
		keywordList[i] = (char*)malloc( sizeof(char) * MAX_DATA);
		if (keywordList[i] == NULL) goto error;
	}


    //argv에서 keywordList로 복사 
	for(int i = 1, index = 0; i < argc; i++){
		if( i  == option)
			continue;
		else{
			strcpy(keywordList[index], argv[i]);
			index++;
		}	
	}

	//for(int i = 0; i < keywordC; i++){
	//	printf("%s\n",keyword[i]);
	//}


	return keywordList;

error:
	return keywordList;

}

