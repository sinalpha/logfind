#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/findfile.h"

char **findFile(int option, char** keywordList, int keywordListC, char** fileNameList, int fileNameListC, int *includingFileC){

	FILE * file				= NULL; //각 파일의 파일 포인터
	char **includingFile 	= NULL; //리턴할 포함하고 있는 파일 목록
	char * line 			= NULL; //각 파일의 행의 내용
	int *checkEx 			= NULL; //and 옵션 체크용 배열, check existence;
	int goal 				= 0;	//각 파일이 포함하고 있어야 할 키워드(검색 키워드)의 갯수
	int sumOfGoal 			= 0;	//각 파일이 포함하고 있는 검색 키워드의 갯수  ex) 검색 키워드: google, facebook, 파일: Hello! google -> 루프후 sumofgoal: 1;
	size_t len 				= 0;	//함수의 인수용 변수
	size_t read;					//함수의 인수용 변수
	

	//키워드의 갯수에 따른 메모리 할당
	checkEx = (int*)calloc( keywordListC, sizeof(int));



	//포함하고 있어야할 키워드 갯수; and 옵션 있음 -> keywordListC, 없음 -> 1. 
	if (option != 0) goal = keywordListC;
	else 			goal = 1;


	//serch including files
	for (int j = 0; j < fileNameListC; j++)
	{
		
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
        	if (sumOfGoal >=  goal)
		{	
			
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
	return includingFile;
}


