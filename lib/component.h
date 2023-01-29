#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wordexp.h>

#define MAX_DATA 100

int returnOption(int argc, char *argv[]){
	//옵션 위치 찾기
	for(int m = 0; m < argc; m++)
		if(strstr(argv[m], "-o") != NULL) return m;
	
	return 0;
}
char **extractKeyword(int argc, char *argv[], int option, int *keywordListC){

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


	return keywordList;

error:
	return NULL;

}
char **readWildFile(int *wildFileListC){

	FILE *file 			= NULL; //logfind의 파일 포인터
	char **wildFileList 		= NULL; //return할 wildFileList
	char *line 			= NULL; //logfind의 라인 내용; ex) logfind의 1번째 라인: *.py\n -> line변수: *.py\n
    	int lineCount 			= 0; 	//logfind의 라인 수 == wildFileListC;  루프용 인덱스 변수 
	int size 			= 0; 	//wildFileList의 메모리 크기
    	int i				= 0; 	//루프용 인덱스 변수
	size_t len 			= 0; 	//함수 인수용 변수
    	ssize_t read 			= 0; 	//logfind의 각 라인의 문자수 ex) logfind의 1번째 라인: *.py\n -> read변수:  

	//.logfind 파일 오픈 
	file = fopen(".logfind","r");
	if(file == NULL){
		printf("None of .logfind, create .logfind first.\n");
		goto error;
	}

    	//읽어 오는 파일 목록 크기 추출
	while( ( read = getline(&line, &len, file) ) != -1 )
    	{    

        
		size 	= sizeof(char*) * ++lineCount;
		i 	 	= lineCount - 1;

		//목록 배열 재할당 2차원
		wildFileList = (char**) realloc(wildFileList, size);
        	if(wildFileList == NULL) goto error;
        
		//목록 배열 할당 1차원
        	wildFileList[i] = (char*)malloc(sizeof(char) * read);
        	if(wildFileList[i] == NULL) goto error;

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
	return NULL;

}
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
	return NULL;

}
char **findFile(int option, char** keywordList, int keywordListC, char** fileNameList, int fileNameListC, int *includingFileC){

	FILE * file		= NULL; //각 파일의 파일 포인터
	char **includingFile 	= NULL; //리턴할 포함하고 있는 파일 목록
	char * line 		= NULL; //각 파일의 행의 내용
	int *checkEx 		= NULL; //and 옵션 체크용 배열, check existence;
	int goal 		= 0;	//각 파일이 포함하고 있어야 할 키워드(검색 키워드)의 갯수
	int sumOfGoal 		= 0;	//각 파일이 포함하고 있는 검색 키워드의 갯수  ex) 검색 키워드: google, facebook, 파일: Hello! google -> 루프후 sumofgoal: 1;
	size_t len 		= 0;	//함수의 인수용 변수
	ssize_t read;			//함수의 인수용 변수
	

	//키워드의 갯수에 따른 메모리 할당
	checkEx = (int*)calloc( keywordListC, sizeof(int));



	//포함하고 있어야할 키워드 갯수; and 옵션 있음 -> keywordListC, 없음 -> 1. 
	if(option != 0) goal = keywordListC;
	else 		goal = 1;


	//serch including files
	for (int j = 0; j < fileNameListC; j++){
		
		file = fopen( fileNameList[j], "r");

		//파일의 모든 라인와 검색 키워드 대조.
		while ( ( read = getline(&line, &len, file)) != - 1 )
		{	
			for (int i = 0; i < keywordListC; i++){
				if (strstr(line , keywordList[i]) != NULL) checkEx[i] = 1;
			
			}
		}

		//sumofgoal 구하기
		for (int i = 0; i < keywordListC; i++) 
			if (checkEx[i] == 1) sumOfGoal += 1;


		//sumofgoal이 goal에 해당하면 including 파일에 저장 ex) 검색 키워드: facbook, google, and option: on, 파일 내용: Hello facebook -> 루프후 해당파일을 저장하지 않음, goal = 2이기. 
        	if (sumOfGoal >=  goal){	
			
			*includingFileC += 1;
			
			includingFile = (char **)realloc( includingFile, sizeof(char*) * (*includingFileC));
			if (includingFile == NULL) goto error;

			includingFile[*includingFileC - 1] = fileNameList[j];
        
		}

		//모든 키워드가 포함 되어 있는지 체크
		sumOfGoal = 0;
		for (int i = 0; i < keywordListC; i++)	checkEx[i] = 0;
        	fclose(file);
	}


	return includingFile;

error:
	if (checkEx) free(checkEx);
	if (file) fclose(file);
	return NULL;
}


#endif

