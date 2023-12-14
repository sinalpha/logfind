#ifndef __READFILENAME_H__
#define __READFILENAME_H__

//공용 함수로 바꾸기
#include <wordexp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/readfilename.h"

#define MAX_DATA 100

char **readFileName(char **wildFileList, int wildFileListC, int *fileNameListC){
	
	char **fileNameList 		= NULL; //리턴할 파일 이름list 
	char **fileNameListTemp 	= NULL; //와일드 카드파일에따른 파일 이름 리스트 임시저장 변수
	int sumOfFileName 		= 0;	//총 읽어와야 할 파일 갯수
	wordexp_t p;


	//총 읽어와야 하는 파일의 갯수 구하기	
	for(int i = 0; i < wildFileListC; i++){
		wordexp(wildFileList[i], &p, 0);
		sumOfFileName += p.we_wordc;
	}


	*fileNameListC = sumOfFileName;	//총 읽어와야 할 파일 갯수 리턴 


	//fileNamelist의 2차원 메모리 할당
	fileNameList = (char**)malloc(sumOfFileName * sizeof(char*));
	if(fileNameList == NULL) goto error;

	//file의 1차원 메모리 할당 및 읽어와야 할 파일의 이름 저장 
	//i: wildFileList 			루프용 인덱스 변수
	//m: fileNameList 			루프용 인덱스 변수
	//j: 와일드 카드에 해당하는 파일 갯수 루프용 인덱스 변수
	for(int i = 0, m = 0; i < wildFileListC; i++){
		
		//와일드 카드에 해당하는 파일 목록 추출
		wordexp(wildFileList[i], &p, 0);
		fileNameListTemp = p.we_wordv;
		
		//1차원 메모리 할당 후 이름 저장
		for(int j = 0; j < p.we_wordc; m++, j++){
			fileNameList[m] = (char*)malloc(sizeof(char) * MAX_DATA);
			if(fileNameList[m] == NULL)  goto error;
			strcpy(fileNameList[m] ,fileNameListTemp[j]);
		}
	}	

	wordfree(&p);
	return fileNameList;

error:
	wordfree(&p);
	return fileNameList;

}


#endif
