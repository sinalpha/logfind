#include <stdio.h>
#include "../include/extractkeyword.h"
#include "../include/extractkeyword.h"
#include "../include/readwild.h"
#include "../include/readfilename.h"
#include "../include/findfile.h"
#include "../include/free.h"


int main(int argc, char *argv[]){

	char **extractArgv 		= NULL;
	char **keywordList 		= NULL;
	char **wildFileList 	= NULL;
	char **fileNameList 	= NULL;
	char **includingFile 	= NULL;
	int keywordListC 		= 0;
	int wildFileListC 		= 0;
	int fileNameListC		= 0;
	int includingFileC 		= 0;
	int option 				= 0;


	if (argc < 2){
		printf("usage: ./logfind (keyword) [-o]\n");
		goto errorCode;
	}


	//시작 인수 추출
	extractArgv = (char**)malloc(sizeof(char*) * argc);
	for (int i = 0; i < argc; i++)
		extractArgv[i] = argv[i];


	//옵션 위치 찾기; 시작 인수에서
	option = returnOption(argc, extractArgv);


	//검색 키워드 추출; 시작 인수에 입력되는 키워드
	keywordList = extractKeyword(argc, extractArgv, option, &keywordListC);
	if (keywordList == NULL) goto error;

	//.logfind에서 점검할 파일 목록 읽기; 와일드 카드 포함
	wildFileList = readWildFile(&wildFileListC);
	if (wildFileList == NULL) goto error;
	
	//현재 디렉토리에서 점검할 파일 목록 읽기; 와드드 카드 제거
	fileNameList = readFileName(wildFileList, wildFileListC, &fileNameListC);
	if (fileNameList == NULL) goto error;

	//키워드를 포함하고 있는 파일 리턴
	includingFile = findFile( option, keywordList, keywordListC, fileNameList, fileNameListC, &includingFileC);
	if (includingFile == NULL) goto error;
		

	//키워드를 포함하고 있는 파일 출력
	for (int i = 0; i < includingFileC; i++)
		printf("%s\n", includingFile[i]);

	return 0;

error:
	if (extractArgv) free(extractArgv);
	freeList(keywordList, keywordListC);
	freeList(wildFileList, wildFileListC);
	freeList(fileNameList, fileNameListC);		
	if (includingFile) free(includingFile);

errorCode:
	return -1;
}
